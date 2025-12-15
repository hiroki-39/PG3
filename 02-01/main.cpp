#include <stdio.h>

template<typename Type>

//二つの引数を比較して小さい方を返す関数
Type Min(Type a, Type b)
{
	return (a < b) ? a : b;
}

int main()
{
	//int型、float型、double型で関数を呼び出す(float型は小数点第一、double型は小数点第二まで)
	int a = 10, b = 20;
	float c = 10.1f, d = 20.2f;
	double e = 10.12, f = 20.23;

	printf("int型の比較: %d と %d で小さい方は %d\n", a, b, Min(a, b));

	printf("float型の比較: %.1f と %.1f で小さい方は %.1f\n", c, d, Min(c, d));

	printf("double型の比較: %.2f と %.2f で小さい方は %.2f\n", e, f, Min(e, f));

	return 0;
}