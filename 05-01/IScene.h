#pragma once
#include "InputManager.h"

enum Scene
{
	TITLE,
	STAGE,
	CLEAR,
};

class IScene
{
protected:

	static int sceneNo;

	// 各シーンが入力を参照するためのポインタ
	InputManager* input_ = nullptr;

public:

	// GameManager からセットされる
	void SetInputManager(InputManager* input) { input_ = input; }

	virtual void Initialize() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;

	virtual ~IScene();

	int GetSceneNo() const { return sceneNo; }
};