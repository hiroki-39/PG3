#include "StageScene.h"
#include <math.h>

void StageScene::Initialize()
{
	// プレイヤー初期化
	playerPosX = 300.0f;
	playerPosY = 350.0f;
	playerSpeed = 10.0f;
	playerRadius = 20.0f;

	// 敵初期化
	enemyPosX = 600.0f;
	enemyPosY = 40.0f;
	ememySpeed = 3.0f;
	enemyRadius = 20.0f;
	isEnemyAlive = true;
	enemyRespawnTimer = 120;

	// 弾初期化
	bulletPosX = 1.0f;
	bulletPosY = 1.0f;
	bulletSpeed = 10.0f;
	bulletRadius = 8.0f;
	isBulletShot = false;

	// 当たり判定初期化
	distancePosX = 0.0f;
	distancePosY = 0.0f;
	distanceLenght = 0.0f;
}

void StageScene::Update()
{
	if (!input_) return;


	/*--- キー入力 ---*/
	if (input_->IsDown(DIK_W))
	{
		playerPosY -= playerSpeed;
	}
	if (input_->IsDown(DIK_S))
	{
		playerPosY += playerSpeed;
	}
	if (input_->IsDown(DIK_D))
	{
		playerPosX += playerSpeed;
	}
	if (input_->IsDown(DIK_A))
	{
		playerPosX -= playerSpeed;
	}

	/*--- 座標の固定 ---*/
	if (playerPosY - playerRadius <= 0.0f)
	{
		playerPosY = 0.0f + playerRadius;
	}

	if (playerPosY + playerRadius >= 720.0f)
	{
		playerPosY = 720.0f - playerRadius;
	}

	if (playerPosX + playerRadius >= 1280.0f)
	{
		playerPosX = 1280.0f - playerRadius;
	}

	if (playerPosX - playerRadius <= 0.0f)
	{
		playerPosX = 0.0f + playerRadius;
	}

	/*--- 弾の処理 ---*/
	if (input_->IsTriggered(DIK_SPACE))
	{
		if (!isBulletShot)
		{
			isBulletShot = true;
			bulletPosX = playerPosX;
			bulletPosY = playerPosY;
		}
	}

	// 弾道計算
	if (isBulletShot)
	{
		bulletPosY -= bulletSpeed;

		if (bulletPosY <= 0.0f)
		{
			isBulletShot = false;
		}
	}

	/*--- 敵の処理 ---*/
	if (isEnemyAlive)
	{
		enemyPosX += ememySpeed;

		if (enemyPosX >= 1260.0f)
		{
			ememySpeed *= -1.0f;
		}
		else if (enemyPosX <= 20.0f)
		{
			ememySpeed *= -1.0f;
		}
	}

	//敵のリスポーン処理
	if (!isEnemyAlive)
	{
		enemyRespawnTimer--;

		if (enemyRespawnTimer <= 0)
		{
			isEnemyAlive = true;
			enemyRespawnTimer = 120;
		}
	}

	/*--- 当たり判定 ---*/
	if (isEnemyAlive && isBulletShot)
	{
		distancePosX = (bulletPosX - enemyPosX);
		distancePosY = (bulletPosY - enemyPosY);
		distanceLenght = sqrtf(distancePosX * distancePosX + distancePosY * distancePosY);

		if (distanceLenght < playerRadius + bulletRadius)
		{
			isEnemyAlive = false;
			isBulletShot = false;

			// 敵が倒れたらクリアへ遷移
			sceneNo = CLEAR;
		}
	}
}

void StageScene::Draw()
{
	// 背景
	Novice::DrawBox(0, 0, 1280, 720, 0.0f, 0xFF808080, kFillModeSolid);

	// 弾
	if (isBulletShot)
	{
		Novice::DrawTriangle(static_cast<int>(bulletPosX), static_cast<int>(bulletPosY - 5),
			static_cast<int>(bulletPosX - 5), static_cast<int>(bulletPosY + 5),
			static_cast<int>(bulletPosX + 5), static_cast<int>(bulletPosY + 5),
			WHITE, kFillModeSolid);
	}

	// 自機
	Novice::DrawBox(static_cast<int>(playerPosX - playerRadius), static_cast<int>(playerPosY - playerRadius),
		static_cast<int>(playerRadius * 2), static_cast<int>(playerRadius * 2),
		0.0f, WHITE, kFillModeSolid);

	// 敵
	if (isEnemyAlive)
	{
		Novice::DrawEllipse(static_cast<int>(enemyPosX), static_cast<int>(enemyPosY),
			static_cast<int>(enemyRadius), static_cast<int>(enemyRadius),
			0.0f, WHITE, kFillModeSolid);
	}
}