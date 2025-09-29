#include <stdio.h>
#include<list>
#include <cstring>

int main()
{
	//1970年時の山手線の駅名をリストでstd::stringを使用せずに管理
	std::list<const char*> yamanotesen = { "Tokyo","Kanda","Akihabara","Okachimachi","Ueno","Uguisudani","Nippori","Tabata","Komagome",
		"Sugamo","Otsuka","Ikebukuro","Mejiro","Takadanobaba","Shin-Okubo","Shinnzyuku","Yoyogi","Harajuku","Shibuya",
		"Ebisu","Meguro","Gohanda","Osaki","Shinagawa","Tamachi","Hamamatsucho","shimbasi","Yurakucho" };

	//リストの内容を順に表示(1970年)
	printf("1970年の山手線\n");
	for (const char* station : yamanotesen)
	{
		printf("%s ", station);
	}

	//西日暮里駅を日暮里と田端の間に追加
	for (auto itr = yamanotesen.begin(); itr != yamanotesen.end(); ++itr)
	{
		if (strcmp(*itr, "Tabata") == 0)
		{
			yamanotesen.insert(itr, "<Nishi-Nippori>");
			break;
		}
	}

	//リストの内容を順に表示(2019年)
	printf("\n\n2019年の山手線\n");
	
	for (const char* station : yamanotesen)
	{
		printf("%s ", station);
	}

	//高輪ゲートウェイ駅を品川と田町の間に追加
	for (auto itr = yamanotesen.begin(); itr != yamanotesen.end(); ++itr)
	{
		if (strcmp(*itr, "Shinagawa") == 0)
		{
			yamanotesen.insert(std::next(itr), "<Takanawa Gateway>");
			break;
		}
	}

	//リストの内容を順に表示(2022年)
	printf("\n\n2022年の山手線\n");
	
	for (const char* station : yamanotesen)
	{
		printf("%s ", station);
	}

	printf("\n");

	return 0;
}
