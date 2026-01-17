#include "TitleScene.h"

void TitleScene::Initialize()
{
	// 必要なら初期化処理
}

void TitleScene::Update()
{
	if (input_)
	{
		// スペースキーでステージへ
		if (input_->IsTriggered(DIK_SPACE))
		{
			sceneNo = STAGE;
		}
	}
}

void TitleScene::Draw()
{
	Novice::DrawBox(0, 0, 1280, 720, 0.0f, 0xFFB3EDFF, kFillModeSolid);
	Novice::ScreenPrintf(540, 320, "TITLE");
	Novice::ScreenPrintf(480, 360, "Press SPACE to Start");
}