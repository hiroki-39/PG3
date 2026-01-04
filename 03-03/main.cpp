#include "Animal.h"
#include "Cat.h"
#include "Dog.h"

int main()
{
    Animal* animals[] = {
        new Dog(),
        new Cat()
    };

    for (Animal* a : animals)
    {
        a->Speak(); 
    }

    for (Animal* a : animals)
    {
        delete a;
    }
}
