#include "Player.h"

Player::Player()
{
	this->pos_ = { 50.0f, 100.0f };
	this->speed_ = 5.0f;
	this->playerRadius = 20.0f; // 半径の初期値
}

void Player::Initialize()
{
	// 初期化処理
}

void Player::Update()
{
	// 更新処理
}

void Player::Draw()
{
	int left = static_cast<int>(this->pos_.x - this->playerRadius);
	int top = static_cast<int>(this->pos_.y - this->playerRadius);
	int width = static_cast<int>(this->playerRadius * 2.0f);
	int height = static_cast<int>(this->playerRadius * 2.0f);

	Novice::DrawBox(left, top, width, height,
		0.0f, WHITE, kFillModeSolid);
}

void Player::MoveRight()
{
	this->pos_.x += this->speed_;
}

void Player::MoveLeft()
{
	this->pos_.x -= this->speed_;
}