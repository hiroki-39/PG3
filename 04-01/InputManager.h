#pragma once
#include <Novice.h>
#include <cstring>

class InputManager
{
public:
	InputManager();
	// フレーム毎に呼ぶ
	void Update();

	// 現在フレームでキーが押されているか
	bool IsDown(int dik) const;
	// 押された瞬間（前フレームは未押下）か
	bool IsTriggered(int dik) const;
	// 離した瞬間（前フレームは押下）か
	bool IsReleased(int dik) const;

	const char* GetKeys() const { return keys_; }
	const char* GetPreKeys() const { return preKeys_; }

private:
	char keys_[256];
	char preKeys_[256];
};