#pragma once

class IShape
{
public:
	// 面積を求める
	virtual float Size() const = 0;

	// 面積を表示する
	virtual void Draw() const = 0;

	// 仮想デストラクタ
	virtual ~IShape() = default;
};

