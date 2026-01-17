#include <Novice.h>
#include "GameManager.h"

const char kWindowTitle[] = "LE2B_04_カトウ_ヒロキ";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// ゲームマネージャー起動
	GameManager manager;
	manager.Run();

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}