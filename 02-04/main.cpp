#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <functional>

// 遅延実行関数
void DelayReveal(std::function<void(int, int)> fn, unsigned int delayMs, int roll, int userGuess)
{
	// 指定時間待機
	Sleep(delayMs);

	// コールバック関数呼び出し
	fn(roll, userGuess);
}

int main()
{
	// 乱数初期化
	srand((unsigned)time(NULL));

	int userGuess = 0;

	// ユーザ入力
	printf("丁(偶数)=0, 半(奇数)=1 を入力してください: ");

	scanf_s("%d", &userGuess);

	// サイコロの出目（1〜6）
	int roll = (rand() % 6) + 1;

	printf("サイコロを振っています...\n");

	// ラムダ式
	std::function<void(int, int)> showResult = [](int roll, int userGuess)
		{
			printf("出目は %d でした。\n", roll);

			if ((roll % 2 == 1 && userGuess == 1) || (roll % 2 == 0 && userGuess == 0))
			{
				printf("正解！\n");
			}
			else
			{
				printf("不正解...\n");
			}
		};

	// 3秒後に結果表示
	DelayReveal(showResult, 3000, roll, userGuess);

	return 0;
}
