#include "./Homework.h"

void	PrintIntArray(int* Array, int ArrayLength);
void	PrintCharArray(char* Array, int ArrayLength);
void	DoBetting(int& BettingMoney, int &PlayerMoney);

void	PrintIntArray(int* Array, int ArrayLength)
{
	for (int ArrCount = 0; ArrCount < ArrayLength; ArrCount++)
	{
		if (ArrCount)
			printf(", ");
		printf("[%d]", Array[ArrCount]);
	}
}

void	PrintCharArray(char* Array, int ArrayLength)
{
	for (int ArrCount = 0; ArrCount < ArrayLength; ArrCount++)
	{
		if (ArrCount)
			printf(", ");
		printf("[%c]", Array[ArrCount]);
	}
}

void	DoBetting(int& BettingMoney, int &PlayerMoney)
{
	// 플레이어의 소지금액 알려주고, 최소 베팅 금액 ~ 플레이어 소지금액 사이로 베팅하도록 한다.
	printf("현재 플레이어의 소지금액은 %d원 입니다.\n", PlayerMoney);
	printf("베팅 금액을 설정해주세요.\n베팅 금액은 %d원부터 %d원까지 입니다.\n", kMinBettingMoney, PlayerMoney);
	std::cin >> BettingMoney;
	while (BettingMoney < kMinBettingMoney || BettingMoney > PlayerMoney)
	{
		std::cin.clear();
		std::cin.ignore(10000, '\n');
		printf("\n");
		printf("잘못 입력하셨습니다.\n");
		printf("베팅 금액을 설정해주세요.\n베팅 금액은 %d원부터 %d원까지 입니다.\n", kMinBettingMoney, PlayerMoney);
		std::cin >> BettingMoney;
	}
	// 플레이어의 자산에서 베팅 금액을 뺀다.
	PlayerMoney -= BettingMoney;
}
