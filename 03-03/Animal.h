#pragma once
#include <iostream>

class Animal
{
public:

    // 鳴く
    virtual void Speak() const
    {
       std::cout << "何かの鳴き声" << std::endl;
    }
};

