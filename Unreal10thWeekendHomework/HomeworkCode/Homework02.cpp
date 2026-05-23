#include "./Homework.h"

void	Homework02_Run(void);

void	Homework02_Run(void)
{
	int	SumValue = 0;
	int	InputVal = 0;

	printf("Homework02_Run\n");
	printf("숫자를 입력해주세요 : ");
	std::cin >> InputVal;
	while (InputVal)
	{
		SumValue += InputVal % 10;
		InputVal /= 10;
	}
	printf("입력한 값의 자릿수 합은 [%d]입니다.\n", SumValue);
}
