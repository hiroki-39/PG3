#include "ClearScene.h"

void ClearScene::Initialize()
{
	// 必要なら初期化処理
}

void ClearScene::Update()
{
	if (input_)
	{
		// スペースでタイトルへ
		if (input_->IsTriggered(DIK_SPACE))
		{
			sceneNo = TITLE;
		}
	}
}

void ClearScene::Draw()
{
	Novice::DrawBox(0, 0, 1280, 720, 0.0f, 0xFFB3EDFF, kFillModeSolid);
	Novice::ScreenPrintf(540, 320, "CLEAR");
	Novice::ScreenPrintf(480, 360, "Press SPACE to Title");
}
