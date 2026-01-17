#pragma once
#include <memory>
#include <Novice.h>
#include "IScene.h"
#include "StageScene.h"
#include "TitleScene.h"
#include "ClearScene.h"
#include "InputManager.h"

class GameManager
{
private:
	std::unique_ptr<IScene> SceneArr_[3];

	int currentSceneNo_;
	int prevSceneNo_;

	// インプット管理
	InputManager inputManager_;

public:
	GameManager();
	~GameManager();

	int Run();
};


