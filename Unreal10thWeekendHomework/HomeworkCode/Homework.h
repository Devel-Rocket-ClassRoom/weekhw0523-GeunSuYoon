#pragma once

#include <iostream>
#include <random>

// 돈 관련 선언
// Homework03과 Homework04에서 쓴다.
const int	StartMoney = 10000;
const int	MinBettingMoney = 100;
const int	EndMoney = 100;

void	Homework02_Run(void);
void	Homework03_Run(void);
void	Homework04_Run(void);
void	Homework05_Run(void);

// 배열 출력 함수
void	PrintIntArray(int* Array, int ArrayLength);
void	PrintCharArray(char* Array, int ArrayLength);
// 베팅 함수. Homework03과 Homework04에서 쓴다.
void	DoBetting(int& BettingMoney, int &PlayerMoney);
