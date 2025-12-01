#include "Enemy.h"
#include <iostream>

void (Enemy::* Enemy::actionTable[])() = {
	
	// 接近
	&Enemy::Approach,

	// 射撃
	&Enemy::Shoot,

	// 離脱
	&Enemy::Escape,

};

Enemy::Enemy()
{
	// フェーズ初期化
	phase_ = 0;
}

void Enemy::Update()
{
	// 現在フェーズの関数を実行
	(this->*actionTable[phase_])();

	// フェーズ切り替え
	phase_ = (phase_ + 1) % 3;
}

void Enemy::Approach()
{
	std::cout << "Enemy : Approach(接近中)..." << std::endl;
}

void Enemy::Shoot()
{
	std::cout << "Enemy : Shoot(射撃中)..." << std::endl;
}

void Enemy::Escape()
{
	std::cout << "Enemy : Escape(離脱中)..." << std::endl;
}