#pragma once
#include <iostream>
#include "Animal.h"


class Dog : public Animal
{
public:
    void Speak() const override
    {
        std::cout << "いぬ:ワンワン" << std::endl;
    }
};

