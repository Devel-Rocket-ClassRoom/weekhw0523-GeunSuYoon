#include "./Homework.h"

const int	ConstCardDeckSize = 14;
const char	ConstCardDeck[ConstCardDeckSize] = { 'A', '1', '2' , '3' , '4' , '5' , '6' , '7' , '8' , '9' , '10' , 'J' , 'Q' , 'K' };
const char	ConstJocker = 'j';
const int	ConstDealerGetKard = 2;

void	Homework04_Run(void);
void	InitCardDeck(char* KardDeck);
void	FisherYatesShuffleChar(char* Array, int Length);

void	Homework04_Run(void)
{
	char	CardDeck[ConstCardDeckSize] = { 0, };
	char	DealerCard[ConstDealerGetKard + 1] = { 0, };

	InitCardDeck(CardDeck);
	FisherYatesShuffleChar(CardDeck, ConstCardDeckSize);

	printf("Homework04_Run\n");
}

void	InitCardDeck(char* KardDeck)
{
	for (int KardDeckCount = 0; KardDeckCount < ConstCardDeckSize; KardDeckCount++)
	{
		KardDeck[KardDeckCount] = ConstCardDeck[KardDeckCount];
	}
}

void	FisherYatesShuffleChar(char* Array, int Length)
{
	//PrintArray(Array, Length);
	//printf("\n");
	for (int ArrayCount = 1; ArrayCount < Length; ArrayCount++)
	{
		int	RandomIdx = rand() % (Length - ArrayCount);
		int	TmpVal = Array[Length - ArrayCount];

		Array[Length - ArrayCount] = Array[RandomIdx];
		Array[RandomIdx] = TmpVal;
	}
	//PrintArray(Array, Length);
}

void	PrintArray(int* Array, int Length)
{
	for (int ArrCount = 0; ArrCount < Length; ArrCount++)
	{
		if (ArrCount)
			printf(", ");
		printf("[%d]", Array[ArrCount]);
	}
}
