#pragma once
#include <Novice.h>
#include <math.h>
#include "Vector2.h"

class Player
{
private:

	Vector2 pos_;
	float speed_;
	float playerRadius;

public:
	Player();

	void Initialize();
	void Update();
	void Draw();

	// メンバ関数
	void MoveRight();
	void MoveLeft();
};

