#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <map>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <algorithm>

// シンプルな CSV ローダ（1行はカンマ区切りの整数列）
bool load_csv(const std::string & path, std::vector<std::vector<int>>&outGrid, std::string & err)
{
    std::ifstream ifs(path.c_str());
    if (!ifs)
    {
        err = "ファイルを開けません: " + path;
        return false;
    }

    outGrid.clear();
    std::string line;
    while (std::getline(ifs, line))
    {
        if (line.empty()) continue;
        std::vector<int> row;
        std::stringstream ss(line);
        std::string token;
        while (std::getline(ss, token, ','))
        {
            // 空白
            token.erase(token.begin(), std::find_if(token.begin(), token.end(), [](int ch) { return !std::isspace(ch); }));
            token.erase(std::find_if(token.rbegin(), token.rend(), [](int ch) { return !std::isspace(ch); }).base(), token.end());
            if (token.empty()) continue;
            try
            {
                int v = std::stoi(token);
                row.push_back(v);
            }
            catch (...)
            {
                err = "CSV の値が整数ではありません: " + token;
                return false;
            }
        }
        if (!row.empty()) outGrid.push_back(row);
    }

    if (outGrid.empty())
    {
        err = "CSV に有効なデータがありません";
        return false;
    }

    return true;
}

// 実行時にサンプル CSV を作る
void create_sample_csv(const std::string& path)
{
    std::ofstream ofs(path.c_str());
    if (!ofs) return;
    // 0:空地, 1:壁, 2:水, 3:山, 4:森
    ofs <<
        "1,1,1,1,1,1,1,1,1,1\n"
        "1,0,0,0,2,2,0,0,0,1\n"
        "1,0,4,4,0,0,3,3,0,1\n"
        "1,0,4,4,0,0,3,3,0,1\n"
        "1,0,0,0,0,0,0,0,0,1\n"
        "1,2,2,0,0,0,0,2,2,1\n"
        "1,0,0,3,3,0,0,0,0,1\n"
        "1,0,0,3,3,0,0,0,0,1\n"
        "1,0,0,0,0,0,0,0,0,1\n"
        "1,1,1,1,1,1,1,1,1,1\n";
}

// マップチップ ID -> 表示文字マップ
char tile_to_char(int id)
{
    static std::map<int, char> palette = {
        {0, '.'}, // 空地
        {1, '#'}, // 壁
        {2, '~'}, // 水
        {3, '^'}, // 山
        {4, 'T'}  // 森（Tree）
    };
    auto it = palette.find(id);
    if (it != palette.end()) return it->second;
    return '?';
}

int main()
{
    const std::string csvPath = "map.csv";

    // CSV ロードをバックグラウンドで行うための同期機構
    std::mutex m;
    std::condition_variable cv;
    bool loadFinished = false;
    bool loadSuccess = false;
    std::string loadError;
    std::vector<std::vector<int>> grid;

    // サンプル CSV がなければ生成（メインスレッドで簡易処理）
    {
        std::ifstream test(csvPath.c_str());
        if (!test)
        {
            create_sample_csv(csvPath);
            std::cout << "サンプル CSV を作成しました: " << csvPath << std::endl;
        }
    }

    // バックグラウンドスレッドで CSV を読み込む
    std::thread loader([&]()
        {
            std::string err;
            bool ok = load_csv(csvPath, grid, err);
            {
                std::lock_guard<std::mutex> lk(m);
                loadFinished = true;
                loadSuccess = ok;
                loadError = err;
            }
            cv.notify_one();
        });

    // メインスレッドで読み込み完了を待つ間に別作業（ここでは簡易メッセージ）
    {
        std::unique_lock<std::mutex> lk(m);
        while (!loadFinished)
        {
            // 読み込み中の表示（待機）
            std::cout << "CSV を読み込み中..." << std::endl;
            // 最長1秒待つ（ポーリング表示用）
            cv.wait_for(lk, std::chrono::seconds(1));
        }
    }

    // ローダスレッドを確実に join
    if (loader.joinable()) loader.join();

    if (!loadSuccess)
    {
        std::cerr << "CSV 読み込み失敗: " << loadError << std::endl;
        return 1;
    }

    // grid を確認
    const size_t rows = grid.size();
    const size_t cols = grid[0].size();

    // ASCII マップ出力バッファ（各行は string）
    std::vector<std::string> asciiMap(rows);

    // 並列処理: std::thread を用いて行ごとに分割して処理する
    unsigned int hw = std::thread::hardware_concurrency();
    if (hw == 0) hw = 2; // 実行環境によっては 0 が返ることがある
    unsigned int numWorkers = static_cast<unsigned int>(std::min<size_t>(hw, rows));
    if (numWorkers == 0) numWorkers = 1;

    std::vector<std::thread> workers;
    workers.reserve(numWorkers);

    // 分割範囲を算出
    auto rowsPer = rows / numWorkers;
    auto rem = rows % numWorkers;
    size_t start = 0;

    for (unsigned int w = 0; w < numWorkers; ++w)
    {
        size_t count = rowsPer + (w < rem ? 1 : 0);
        size_t s = start;
        size_t e = s + count; // [s, e)
        start = e;

        workers.emplace_back([s, e, &grid, &asciiMap]()
            {
                for (size_t r = s; r < e; ++r)
                {
                    std::string line;
                    line.reserve(grid[r].size());
                    for (size_t c = 0; c < grid[r].size(); ++c)
                    {
                        line.push_back(tile_to_char(grid[r][c]));
                    }
                    asciiMap[r] = line; // スレッドごとに異なる行へ書き込み -> データ競合無し
                }
            });
    }

    // ワーカーを join
    for (auto& t : workers) if (t.joinable()) t.join();

    // 表示（マップチップとして標準出力）
    std::cout << "\n---- マップ (ASCII 表示) ----\n";
    for (size_t r = 0; r < rows; ++r)
    {
        std::cout << asciiMap[r] << "\n";
    }
    std::cout << "----------------------------\n";

    return 0;
}