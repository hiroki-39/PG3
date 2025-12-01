#pragma once
class Enemy
{
public:

	Enemy();

	// 更新
	void Update();

	// 接近
	void Approach();

	// 射撃
	void Shoot();

	// 離脱
	void Escape();

private:

	// アクションテーブル
	static void (Enemy::* actionTable[])();

	// 現在のフェーズ
	size_t phase_ = 0;
};

