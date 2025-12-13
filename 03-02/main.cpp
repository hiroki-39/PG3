#include <iostream>

template <class T, class U>
class Compare
{
public:
	Compare(T a, U b)
		: a_(a), b_(b)
	{
	}

	// 小さい値をdoubleに変換して返す
	auto min() const
	{
		return (a_ < b_) ? a_ : b_;
	}

private:
	T a_;
	U b_;
};

int main()
{

	// ① int - int
	Compare<int, int> c1(10, 3);
	std::cout << "int-int: " << c1.min() << std::endl;

	// ② float - float
	Compare<float, float> c2(5.5f, 8.1f);
	std::cout << "float-float: " << c2.min() << std::endl;

	// ③ double - double
	Compare<double, double> c3(3.14, 2.71);
	std::cout << "double-double: " << c3.min() << std::endl;

	// ④ int - float
	Compare<int, float> c4(10, 5.5f);
	std::cout << "int-float: " << c4.min() << std::endl;

	// ⑤ int - double
	Compare<int, double> c5(10, 2.71);
	std::cout << "int-double: " << c5.min() << std::endl;

	// ⑥ float - double
	Compare<float, double> c6(5.5f, 3.14);
	std::cout << "float-double: " << c6.min() << std::endl;

	return 0;
}