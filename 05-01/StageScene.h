#pragma once
#include <Novice.h>
#include "IScene.h"
#include "InputHandler.h"
#include "Player.h"
#include "Command.h"

class StageScene : public IScene
{
public:
	StageScene();
	~StageScene() override;

	void Initialize() override;
	void Update() override;
	void Draw() override;

private:
	InputHandler* inputHandler_ = nullptr;
	Player* player_ = nullptr;
	ICommand* iCommand_ = nullptr;
};