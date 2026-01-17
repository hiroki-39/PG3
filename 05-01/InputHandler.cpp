#include "InputHandler.h"
#include "InputManager.h"

InputHandler::InputHandler()
	: pressKeyD_(nullptr)
	, pressKeyA_(nullptr)
{
}

InputHandler::~InputHandler()
{
	if (pressKeyD_)
	{
		delete pressKeyD_;
		pressKeyD_ = nullptr;
	}
	if (pressKeyA_)
	{
		delete pressKeyA_;
		pressKeyA_ = nullptr;
	}
}

ICommand* InputHandler::HandleInput(InputManager* input)
{
	if (input == nullptr) return nullptr;

	// 押されている間に移動させたいので IsDown を使用
	if (input->IsDown(DIK_D))
	{
		return pressKeyD_;
	}
	if (input->IsDown(DIK_A))
	{
		return pressKeyA_;
	}

	return nullptr;
}

void InputHandler::AssignMoveLeftCommandPressKeyA()
{
	ICommand* command = new MoveLeftCommand();
	this->pressKeyA_ = command;
}

void InputHandler::AssignMoveRightCommandPressKeyD()
{
	ICommand* command = new MoveRightCommand();
	this->pressKeyD_ = command;
}