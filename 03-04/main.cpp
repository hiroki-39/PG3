#include "Rectangle.h"
#include "Circle.h"

int main()
{
    IShape* shape1 = new Circle(5.0f);
    IShape* shape2 = new Rectangle(4.0f, 6.0f);

    shape1->Draw();
    shape2->Draw();

    delete shape1;
    delete shape2;

	return 0;
}
