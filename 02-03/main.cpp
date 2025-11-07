#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

// 判定関数のプロトタイプ
void ShowResult(int roll, int userGuess);

// 遅延実行関数
void DelayReveal(void (*fn)(int, int), unsigned int delayMs, int roll, int userGuess)
{
	// 指定時間待機
	Sleep(delayMs);

	// コールバック関数呼び出し
	fn(roll, userGuess);
}

// 結果表示関数
void ShowResult(int roll, int userGuess)
{
	printf("出目は %d でした。\n", roll);

	// 奇数判定 → roll % 2 == 1
	// 偶数判定 → roll % 2 == 0
	if ((roll % 2 == 1 && userGuess == 1) || (roll % 2 == 0 && userGuess == 0))
	{
		printf("正解！\n");
	}
	else
	{
		printf("不正解...\n");
	}
}

int main()
{
	// 乱数の初期化
	srand((unsigned)time(NULL));

	int userGuess = 0;

	// ユーザ入力（0=偶数 / 1=奇数）
	printf("丁(偶数)=0, 半(奇数)=1 を入力してください: ");
	scanf_s("%d", &userGuess); // 入力値は 0 or 1 を想定

	// サイコロの出目（1〜6）
	int roll = (rand() % 6) + 1;

	printf("サイコロを振っています...\n");

	// 3秒後に結果表示
	DelayReveal(ShowResult, 3000, roll, userGuess);

	return 0;
}
