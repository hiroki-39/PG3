#pragma once
#include <Novice.h>
#include "IScene.h"

class StageScene : public IScene
{
public:
	void Initialize() override;
	void Update() override;
	void Draw() override;
private:
	// プレイヤー
	float playerPosX;
	float playerPosY;
	float playerSpeed;
	float playerRadius;

	// 敵
	float enemyPosX;
	float enemyPosY;
	float ememySpeed;
	float enemyRadius;
	bool isEnemyAlive;
	int enemyRespawnTimer;

	// 弾
	float bulletPosX;
	float bulletPosY;
	float bulletSpeed;
	float bulletRadius;
	bool isBulletShot;

	// 当たり判定
	float distancePosX;
	float distancePosY;
	float distanceLenght;
};

