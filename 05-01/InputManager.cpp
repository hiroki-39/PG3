#include "InputManager.h"

InputManager::InputManager()
{
	std::memset(keys_, 0, sizeof(keys_));
	std::memset(preKeys_, 0, sizeof(preKeys_));
}

void InputManager::Update()
{
	std::memcpy(preKeys_, keys_, sizeof(keys_));
	Novice::GetHitKeyStateAll(keys_);
}

bool InputManager::IsDown(int dik) const
{
	return keys_[dik] != 0;
}

bool InputManager::IsTriggered(int dik) const
{
	return (keys_[dik] != 0) && (preKeys_[dik] == 0);
}

bool InputManager::IsReleased(int dik) const
{
	return (keys_[dik] == 0) && (preKeys_[dik] != 0);
}