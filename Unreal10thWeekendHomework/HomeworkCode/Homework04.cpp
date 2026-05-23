#include "./Homework.h"

// 전역 상수 선언부
// 카드 관련 선언
const int	kCardDeckSize = 13;
const char	kCardDeck[kCardDeckSize] = { 'A', '2' , '3' , '4' , '5' , '6' , '7' , '8' , '9' , '10' , 'J' , 'Q' , 'K' };
const char	kJocker = 'j';
const int	kDealerGetCard = 2;
// 베팅 배수 선언
const int	kOldMaid = 2;

void	Homework04_Run(void);
void	PrintOldMaidInformation(void);
void	InitCardDeck(char* CardDeck);
void	DealerSelectCard(char* CardDeck, char* DealerCard);
void	FisherYatesShuffleChar(char* Array, int Length);
int		ChoiceCard(void);

void	Homework04_Run(void)
{
	int		PlayerMoney = kStartMoney;
	int		BettingMoney = 0;
	char	CardDeck[kCardDeckSize] = { 0, };
	char	DealerCard[kDealerGetCard + 1] = { 0, };

	printf("Homework04_Run\n");
	InitCardDeck(CardDeck);
	PrintOldMaidInformation();
	while (PlayerMoney >= kEndMoney)
	{
		printf("\n============================================================\n");
		if (!BettingMoney)
		{
			// 베팅하기. 함수는 util.cpp에 정의했다.
			DoBetting(BettingMoney, PlayerMoney);
		}
		else
		{
			// 베팅 금액이 존재 할 때는 이전 게임에서 2배로 베팅한 것이다.
			printf("현재 플레이어의 소지금은 %d원 입니다.\n베팅 금액은 %d원 입니다.\n", PlayerMoney, BettingMoney);
		}
		// 딜러가 카드 세 장 뽑는 함수
		DealerSelectCard(CardDeck, DealerCard);
		// 플레이어가 세 장중 한 장 고르는 함수
		int	SelectedCard = ChoiceCard();
		printf("딜러의 카드는 아래와 같습니다.\n");
		PrintCharArray(DealerCard, kDealerGetCard + 1);
		if (DealerCard[SelectedCard] != kJocker)
		{
			printf("도둑을 못찾았습니다...\n");
			printf("게임을 다시 시작하거나 베팅 금액의 2배를 다시 베팅할 수 있습니다.\n");
			printf("새로운 베팅 금액은 %d원입니다.\n", BettingMoney * 2);
			printf("어떻게 할 건지 선택해주세요.\n");
			printf("1. 다음 게임 시작	2. 묻고 더블로 가\n");
			int	NextGameState = 0;
			std::cin >> NextGameState;
			while (NextGameState != 1 && NextGameState != 2)
			{
				std::cin.clear();
				std::cin.ignore(10000, '\n');
				printf("잘못 입력하셨습니다.\n");
				printf("1. 다음 게임 시작	2. 묻고 더블로 가\n");
				std::cin >> NextGameState;
			}
			if (NextGameState == 1)
			{
				printf("다음 게임을 시작하겠습니다.\n");
				BettingMoney = 0;
			}
			else
			{
				printf("묻고 더블로 가겠습니다.\n");
				BettingMoney *= 2;
				if (PlayerMoney < BettingMoney)
				{
					printf("플레이어 소지금이 부족합니다.\n");
					printf("다음 게임을 시작하겠습니다.\n");
					BettingMoney = 0;
				}
			}
		}
		else
		{
			printf("도둑을 찾았습니다!\n");
			printf("베팅 금액 %d의 %d배인 %d원을 획득했습니다!\n", BettingMoney, kOldMaid, BettingMoney * kOldMaid);
			PlayerMoney += BettingMoney * kOldMaid;
			BettingMoney = 0;
		}
	}
	printf("소지 금액이 %d원 입니다.\n파산했습니다...\n", PlayerMoney);
}

void	PrintOldMaidInformation(void)
{
	printf("게임 규칙 설명=========================================\n");
	printf("카드의 개수는 %d개 입니다.\n", kCardDeckSize + 1);
	printf("딜러는 %d개의 카드를 뽑은 뒤, 조커를 포함해 총 %d개의 카드를 가집니다.\n", kDealerGetCard, kDealerGetCard + 1);
	printf("조커를 찾으시면 베팅 금액의 %d배를 획득하실 수 있습니다.\n", kOldMaid);
	printf("찾지 못했다면 다음 게임을 진행하거나.\n");
	printf("베팅 금액의 2배를 지불해 게임을 진행할 수 있습니다.\n");
	printf("도박은 위험합니다...\n");
	printf("=====================================================\n");
}

// 최초 카드덱 설정 함수
void	InitCardDeck(char* CardDeck)
{
	for (int CardDeckCount = 0; CardDeckCount < kCardDeckSize; CardDeckCount++)
	{
		CardDeck[CardDeckCount] = kCardDeck[CardDeckCount];
	}
}

// 딜러가 카드를 섞고 2장을 뽑은 뒤 조커를 포함해 딜러의 카드 세 장을 섞는 함수
void	DealerSelectCard(char* CardDeck, char* DealerCard)
{
	FisherYatesShuffleChar(CardDeck, kCardDeckSize);
	DealerCard[0] = CardDeck[0];
	DealerCard[1] = CardDeck[1];
	DealerCard[2] = kJocker;
	FisherYatesShuffleChar(DealerCard, kDealerGetCard + 1);
}

// 피셔-예이츠 셔플.
void	FisherYatesShuffleChar(char* Array, int Length)
{
	for (int ArrayCount = 1; ArrayCount < Length; ArrayCount++)
	{
		int	RandomIdx = rand() % (Length - ArrayCount);
		int	TmpVal = Array[Length - ArrayCount];

		Array[Length - ArrayCount] = Array[RandomIdx];
		Array[RandomIdx] = TmpVal;
	}
}

int	ChoiceCard(void)
{
	int	ReturnIntValue = -1;

	printf("딜러의 카드를 선택해주세요.\n");
	printf("1부터 3 사이 숫자 중 하나를 고르시면 됩니다.");
	std::cin >> ReturnIntValue;
	while (ReturnIntValue < 1 || ReturnIntValue > kDealerGetCard + 1)
	{
		std::cin.clear();
		std::cin.ignore(10000, '\n');
		printf("\n");
		printf("잘못 입력하셨습니다.\n");
		printf("1부터 3 사이 숫자 중 하나를 고르시면 됩니다.");
		std::cin >> ReturnIntValue;
	}
	return (ReturnIntValue - 1);
}
