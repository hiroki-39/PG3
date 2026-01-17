#pragma once
#include <Novice.h>
#include "Command.h"

class InputManager; // 前方宣言

class InputHandler
{
public:
	InputHandler();
	~InputHandler();

	// InputManager の状態を参照して ICommand を返す
	ICommand* HandleInput(InputManager* input);

	void AssignMoveLeftCommandPressKeyA();
	void AssignMoveRightCommandPressKeyD();

private:
	ICommand* pressKeyD_;
	ICommand* pressKeyA_;
};

