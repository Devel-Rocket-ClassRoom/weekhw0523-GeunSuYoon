#include "./Homework.h"

// enum 선언부
// const char	SlotMachineSymbol 과 연결되는 enum.
// 한 쪽을 바꿔주면 여기도 바꿔줘야 한다!
enum ESlotSymbol
{
	SlotSymbolSeven		= 0,
	SlotSymbolJack		= 1,
	SlotSymbolQueen		= 2,
	SlotSymbolKing	= 3,
};
// 슬롯 결과 enum.
enum ESlotMatch
{
	SlotMatchFail	= 0,	// 베팅 금액 다 잃기
	SlotMatchSeven	= 1,	// 베팅 금액 LuckySeven배 만큼 얻기
	SlotMatchTriple	= 2,	// 베팅 금액 TripleNum배 만큼 얻기
};
// 전역변수 선언부
const int	StartCost = 10000;
const int	MinBettingCost = 100;
const int	EndCost = 100;
// 베팅 금액 돌려받는 배수
const int	TripleNum = 50;
const int	LuckySeven = 10000;
// 슬롯 관련 선언부
// 여길 바꾸면 enum도 바꿔줘야 한다!
const int	SlotSymbolSize = 4;
const char	SlotMachineSymbol[SlotSymbolSize] = { '7', 'J', 'Q', 'K' };
// 슬롯 머신 심볼 개수
const int	SlotMachineSize = 3;

void		Homework03_Run(void);
void		PrintSlotMachine(ESlotSymbol* SlotMachine);
ESlotMatch	CheckResult(ESlotSymbol* SlotMachine);

void	Homework03_Run(void)
{
	// 사용할 변수 선언부
	int			PlayerCost = StartCost;
	int			BettingCost = 0;
	ESlotSymbol	SlotMachine[SlotMachineSize] = { SlotSymbolSeven, SlotSymbolSeven, SlotSymbolSeven };

	printf("Homework03_Run\n");
	// 초기 설정 알려주는 곳
	printf("슬롯 머신의 슬롯은 %d개입니다.\n", SlotMachineSize);
	printf("슬롯 머신의 심볼은 %d개이며 아래와 같습니다.\n", SlotSymbolSize);
	for (int SlotSymbolCount = 0; SlotSymbolCount < SlotSymbolSize; SlotSymbolCount++)
	{
		if (SlotSymbolCount)
			printf(", ");
		printf("[%c]", SlotMachineSymbol[SlotSymbolCount]);
	}
	printf("\n");
	PrintSlotMachine(SlotMachine);
	while (PlayerCost >= EndCost)
	{
		// 플레이어의 소지금액 알려주고, 최소 베팅 금액 ~ 플레이어 소지금액 사이로 베팅하도록 한다.
		printf("현재 플레이어의 소지금액은 %d원 입니다.\n", PlayerCost);
		printf("베팅 금액을 설정해주세요.\n베팅 금액은 %d원부터 %d원까지 입니다.\n", MinBettingCost, PlayerCost);
		std::cin >> BettingCost;
		while (BettingCost < 100 || BettingCost > PlayerCost)
		{
			std::cin.clear();
			std::cin.ignore(10000, '\n');
			printf("베팅 금액을 설정해주세요.\n베팅 금액은 %d원부터 %d원까지 입니다.\n", MinBettingCost, PlayerCost);
			std::cin >> BettingCost;
		}
		// 플레이어의 자산에서 베팅 금액을 뺀다.
		PlayerCost -= BettingCost;
		// 슬롯 머신 결과 출력
		for (int SlotMachineCount = 0; SlotMachineCount < SlotMachineSize; SlotMachineCount++)
		{
			int	SlotResult = rand() % SlotSymbolSize;

			SlotMachine[SlotMachineCount] = static_cast<ESlotSymbol>(SlotResult);
		}
		PrintSlotMachine(SlotMachine);
		// 슬롯 머신 결과 확인 후 베팅 금액을 돌려받거나 그대로 놔두던가 한다.
		ESlotMatch	SlotMatch = CheckResult(SlotMachine);
		switch (SlotMatch)
		{
		case (SlotMatchFail):
		{
			printf("슬롯이 빗나갔습니다...\n\n");
			break;
		}
		case (SlotMatchTriple):
		{
			printf("Triple!!!\n");
			printf("베팅 금액 %d원의 %d배인 %d원을 얻었습니다!\n\n", BettingCost, TripleNum, BettingCost * TripleNum);
			PlayerCost += BettingCost * TripleNum;
			break;
		}
		case (SlotMatchSeven):
		{
			printf("★☆★☆★☆★☆Lucky Seven!!!★☆★☆★☆★☆\n");
			printf("베팅 금액 %d원의 %d배인 %d원을 얻었습니다!!!\n", BettingCost, LuckySeven, BettingCost * LuckySeven);
			printf("★☆★☆★☆★☆Lucky Seven!!!★☆★☆★☆★☆\n\n");
			PlayerCost += BettingCost * LuckySeven;
			break;
		}
		default:
		{
			printf("Error: ESlotMatch에서 나올 수 없는 값이 반환됐습니다.\n\n");
			break;
		}
		}
		BettingCost = 0;
	}
	printf("소지 금액이 %d원 입니다.\n파산했습니다...\n", PlayerCost);
}

void	PrintSlotMachine(ESlotSymbol* SlotMachine)
{
	printf("Slot Machine\n");
	for (int SlotMachineCount = 0; SlotMachineCount < SlotMachineSize; SlotMachineCount++)
	{
		printf("   -   ");
	}
	printf("\n");
	for (int SlotMachineCount = 0; SlotMachineCount < SlotMachineSize; SlotMachineCount++)
	{
		printf("| [%c] |", SlotMachineSymbol[SlotMachine[SlotMachineCount]]);
	}
	printf("\n");
	for (int SlotMachineCount = 0; SlotMachineCount < SlotMachineSize; SlotMachineCount++)
	{
		printf("   -   ");
	}
	printf("\n");
	printf("Slot Machine\n");
}

ESlotMatch	CheckResult(ESlotSymbol* SlotMachine)
{
	ESlotSymbol	CheckSlot = SlotMachine[0];

	for (int SlotMachineCount = 0; SlotMachineCount < SlotMachineSize; SlotMachineCount++)
	{
		if (CheckSlot != SlotMachine[SlotMachineCount])
			return (SlotMatchFail);
	}
	if (CheckSlot == SlotSymbolSeven)
		return (SlotMatchSeven);
	else
		return (SlotMatchTriple);
}
