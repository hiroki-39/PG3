#pragma once
#include <iostream>
#include "IShape.h"

class Rectangle : public IShape
{
public:

	// コンストラクタ
    Rectangle(float width, float height)
        : width_(width), height_(height)
    {
    }

	// 面積を求める
    float Size() const override
    {
        return width_ * height_;
    }

	// 面積を表示
    void Draw() const override
    {
        std::cout << "Rectangle:" << Size() << std::endl;
    }

private:

	// 幅
    float width_;

	// 高さ
    float height_;
};

