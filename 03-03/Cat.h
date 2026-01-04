#pragma once
#include "Animal.h"
#include <iostream>
class Cat : public Animal
{
public:
	void Speak() const override
	{
		std::cout << "ねこ:ニャーニャー" << std::endl;
	}
};

