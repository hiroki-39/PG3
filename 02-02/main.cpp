#include <stdio.h>

/// <summary>
///  一般的な賃金体系での総賃金を再帰的に計算
/// </summary>
/// <param name="hours">時間</param>
/// <param name="wagePerHour">時給</param>
int calcNormalWage(int hours, int wagePerHour)
{
	if (hours <= 0)
	{
		return 0;
	}

	return wagePerHour + calcNormalWage(hours - 1, wagePerHour);
}

/// <summary>
///  再帰的な賃金体系での総賃金を再帰的に計算
/// </summary>
/// <param name="hours">時間</param>
/// <param name="currentWage">現在の時給</param>
int calcRecursiveWage(int hours, int currentWage)
{
	if (hours <= 0)
	{
		return 0;
	}

	// 現在の時給を足して、次の時間の時給を再帰的に計算
	return currentWage + calcRecursiveWage(hours - 1, currentWage * 2 - 50);
}

int main(void)
{
	const int normalWagePerHour = 1226; // 一般的な賃金
	const int firstRecursiveWage = 100; // 再帰的賃金の最初の時給

	int hoursWorked = 0;

	while (true)
	{
		++hoursWorked;

		int totalNormal = calcNormalWage(hoursWorked, normalWagePerHour);
		int totalRecursive = calcRecursiveWage(hoursWorked, firstRecursiveWage);

		if (totalRecursive > totalNormal)
		{
			printf("再帰的な賃金体系が一般的な賃金体系を上回るのは %d 時間目です。\n\n", hoursWorked);
			printf("一般的な賃金体系での総賃金: %d 円\n", totalNormal);
			printf("再帰的な賃金体系での総賃金: %d 円\n", totalRecursive);
			break;
		}

		// 無限ループ防止
		if (hoursWorked > 10000)
		{
			printf("10000時間働いても再帰的賃金は上回りませんでした。\n");
			break;
		}
	}

	return 0;
}
