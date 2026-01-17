#include "GameManager.h"

GameManager::GameManager()
{
	SceneArr_[TITLE] = std::make_unique<TitleScene>();
	SceneArr_[STAGE] = std::make_unique<StageScene>();
	SceneArr_[CLEAR] = std::make_unique<ClearScene>();

	// 各シーンに InputManager を注入
	for (int i = 0; i < 3; ++i)
	{
		SceneArr_[i]->SetInputManager(&inputManager_);
	}

	// 初期シーン設定
	currentSceneNo_ = STAGE;
	prevSceneNo_ = -1;
}

GameManager::~GameManager()
{
}

int GameManager::Run()
{
	// 初回シーンの初期化
	SceneArr_[currentSceneNo_]->Initialize();

	while (Novice::ProcessMessage() == 0)
	{
		Novice::BeginFrame(); // フレームの開始

		// 入力更新
		inputManager_.Update();

		// シーンのチェック
		prevSceneNo_ = currentSceneNo_;
		currentSceneNo_ = SceneArr_[currentSceneNo_]->GetSceneNo();

		// シーン変更チェック
		if (prevSceneNo_ != currentSceneNo_)
		{
			SceneArr_[currentSceneNo_]->Initialize();
		}

		// 更新処理
		SceneArr_[currentSceneNo_]->Update();
		// 描画処理
		SceneArr_[currentSceneNo_]->Draw();

		// デバッグ表示
		Novice::ScreenPrintf(10, 320, "SceneNo = %d", currentSceneNo_);
		Novice::ScreenPrintf(10, 340, "Push ESC to quit");

		Novice::EndFrame(); // フレームの終了

		// ESCキーが押されたらループを抜ける
		if (inputManager_.IsTriggered(DIK_ESCAPE))
		{
			break;
		}
	}

	return 0;
}