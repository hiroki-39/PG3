#pragma once
#include <iostream>
#include "IShape.h"


class Circle : public IShape
{
public:

	// コンストラクタ
    Circle(float radius) : radius_(radius) {}

	// 面積を求める
    float Size() const override
    {
        return radius_ * radius_ * 3.141592f;
    }

	// 面積を表示
    void Draw() const override
    {
        std::cout << "Circle:" << Size() << std::endl;
    }

private:
	// 半径
    float radius_;
};

