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
// 전역 상수 선언부
// 돈 관련 선언
//const int	StartMoney = 10000;
//const int	MinBettingMoney = 100;
//const int	EndMoney = 100;
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
	int			PlayerMoney = StartMoney;
	int			BettingMoney = 0;
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
	while (PlayerMoney >= EndMoney)
	{
		// 베팅하기. 함수는 util.cpp에 정의했다.
		DoBetting(BettingMoney, PlayerMoney);
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
			printf("베팅 금액 %d원의 %d배인 %d원을 얻었습니다!\n\n", BettingMoney, TripleNum, BettingMoney * TripleNum);
			PlayerMoney += BettingMoney * TripleNum;
			break;
		}
		case (SlotMatchSeven):
		{
			printf("★☆★☆★☆★☆Lucky Seven!!!★☆★☆★☆★☆\n");
			printf("베팅 금액 %d원의 %d배인 %d원을 얻었습니다!!!\n", BettingMoney, LuckySeven, BettingMoney * LuckySeven);
			printf("★☆★☆★☆★☆Lucky Seven!!!★☆★☆★☆★☆\n\n");
			PlayerMoney += BettingMoney * LuckySeven;
			break;
		}
		default:
		{
			printf("Error: ESlotMatch에서 나올 수 없는 값이 반환됐습니다.\n\n");
			break;
		}
		}
		BettingMoney = 0;
	}
	printf("소지 금액이 %d원 입니다.\n파산했습니다...\n", PlayerMoney);
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
