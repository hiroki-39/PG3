#include "StageScene.h"
#include <math.h>

StageScene::StageScene()
{
}

StageScene::~StageScene()
{
	if (inputHandler_)
	{
		delete inputHandler_;
		inputHandler_ = nullptr;
	}
	if (player_)
	{
		delete player_;
		player_ = nullptr;
	}
}

void StageScene::Initialize()
{
	inputHandler_ = new InputHandler();

	inputHandler_->AssignMoveRightCommandPressKeyD();
	inputHandler_->AssignMoveLeftCommandPressKeyA();

	player_ = new Player();
}

void StageScene::Update()
{
	if (!input_) return;

	iCommand_ = inputHandler_->HandleInput(input_);

	if (this->iCommand_)
	{
		iCommand_->Execute(*player_);
	}

	player_->Update();
}

void StageScene::Draw()
{
	// プレイヤー描画
	if (player_)
	{
		player_->Draw();
	}
}