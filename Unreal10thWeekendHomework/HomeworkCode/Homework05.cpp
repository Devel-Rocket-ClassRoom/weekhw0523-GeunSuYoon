#include "./Homework.h"

// enum 선언부
// 미로 심볼 선언
// const char	kMazeSymbol과 대응되는 enum이며, 둘 중 하나라도 변경하면 같이 변경해야 한다.
enum EMazeSymbol
{
	MazeSymbol_Way		= 0,	// 미로 길
	MazeSymbol_Wall		= 1,	// 미로 벽
	MazeSymbol_Start	= 2,	// 미로 시작
	MazeSymbol_End		= 3,	// 미로 끝
	MazeSymbol_Player	= 4,	// 플레이어 
};
// 미로 상태 체크
enum EMazeState
{
	MazeState_NoError,			// 시작 위치, 출구 다 있는 정상상태 미로
	MazeState_NoStart,			// 시작 위치 없음
	MazeState_NoEnd,			// 출구 없음
	MazeState_DuplicateStart,	// 시작 위치 여러개
	MazeState_DuplicateEnd,		// 종료 위치 여러개
	MazeState_UnknownSymbol,	// Maze 배열에 알 수 없는 값이 있음
	MazeState_CannotExit,		// 탈출할 수 없음
	MazeState_CanExit,			// 탈출할 수 있음 에러는 아니고 미로 탐사 시 종료값으로 쓴다.
};
// 플레이어 움직임 방향 선언
enum EPlayerMoveDirection
{
	PlayerMoveDirection_Up		= 0,	// 위로 이동
	PlayerMoveDirection_Left	= 1,	// 왼쪽으로 이동
	PlayerMoveDirection_Down	= 2,	// 아래로 이동
	PlayerMoveDirection_Right	= 3,	// 오른쪽으로 이동
};
// 방향키 입력 선언
enum EPlayerMoveInput
{
	PlayerMoveInput_UpLower	= 'w',		// 위로 이동
	PlayerMoveInput_UpUpper = 'W',		// 위로 이동
	PlayerMoveInput_LeftLower = 'a',	// 왼쪽으로 이동
	PlayerMoveInput_LeftUpper = 'A',	// 왼쪽으로 이동
	PlayerMoveInput_DownLower = 's',	// 아래로 이동
	PlayerMoveInput_DownUpper = 'S',	// 아래로 이동
	PlayerMoveInput_RightLower = 'd',	// 오른쪽으로 이동
	PlayerMoveInput_RightUpper = 'D',	// 오른쪽으로 이동
};

// 전역 상수 선언부
// 미로 관련 선언
// 미로 가로 세로 크기
const int kMazeCols = 20;
const int kMazeRows = 10;
// 미로 배열
const int kMaze[kMazeRows][kMazeCols] =
{
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,2,0,0,0,1,0,0,0,0,1,0,0,1,0,0,0,1,0,1},
	{1,1,1,1,0,1,0,1,1,0,1,0,1,1,0,1,0,1,0,1},
	{1,0,0,1,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,1},
	{1,0,1,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1},
	{1,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,1},
	{1,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1},
	{1,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,3,1},
	{1,0,1,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};
// 오류 미로 맵 이름을 읽어보면 어떤 오류인지 알 수 있다. 바로 위 kMaze에 덮어써서 확인하면 된다.
const int kMazeNoError[kMazeRows][kMazeCols] =
{
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,2,0,0,0,1,0,0,0,0,1,0,0,1,0,0,0,1,0,1},
	{1,1,1,1,0,1,0,1,1,0,1,0,1,1,0,1,0,1,0,1},
	{1,0,0,1,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,1},
	{1,0,1,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1},
	{1,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,1},
	{1,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1},
	{1,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,3,1},
	{1,0,1,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};
const int kMazeNoStart[kMazeRows][kMazeCols] =
{
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,1,0,0,0,0,1,0,0,1,0,0,0,1,0,1},
	{1,1,1,1,0,1,0,1,1,0,1,0,1,1,0,1,0,1,0,1},
	{1,0,0,1,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,1},
	{1,0,1,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1},
	{1,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,1},
	{1,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1},
	{1,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,3,1},
	{1,0,1,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};
const int kMazeNoEnd[kMazeRows][kMazeCols] =
{
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,2,0,0,0,1,0,0,0,0,1,0,0,1,0,0,0,1,0,1},
	{1,1,1,1,0,1,0,1,1,0,1,0,1,1,0,1,0,1,0,1},
	{1,0,0,1,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,1},
	{1,0,1,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1},
	{1,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,1},
	{1,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1},
	{1,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1},
	{1,0,1,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};
const int kMazeDupStart[kMazeRows][kMazeCols] =
{
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,2,0,0,0,1,0,0,0,0,1,0,0,1,0,0,0,1,0,1},
	{1,1,1,1,0,1,0,1,1,0,1,0,1,1,0,1,0,1,0,1},
	{1,0,0,1,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,1},
	{1,0,1,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1},
	{1,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,1},
	{1,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1},
	{1,0,0,1,0,0,0,1,0,2,0,1,0,0,0,1,0,0,3,1},
	{1,0,1,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};
const int kMazeDupEnd[kMazeRows][kMazeCols] =
{
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,2,0,0,0,1,0,0,0,0,1,0,0,1,0,0,0,1,0,1},
	{1,1,1,1,0,1,0,1,1,0,1,0,1,1,0,1,0,1,0,1},
	{1,0,0,1,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,1},
	{1,0,1,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1},
	{1,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,1},
	{1,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1},
	{1,0,0,1,0,0,0,1,0,3,0,1,0,0,0,1,0,0,3,1},
	{1,0,1,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};
const int kMazeUnkownSymbol[kMazeRows][kMazeCols] =
{
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,2,0,0,0,1,0,0,0,0,1,0,0,1,0,0,0,1,0,1},
	{1,1,1,1,0,1,0,1,1,0,1,0,1,1,0,1,0,1,0,1},
	{1,0,0,1,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,1},
	{1,0,1,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1},
	{1,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,1},
	{1,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1},
	{1,0,0,1,0,4,0,1,0,0,0,1,0,0,0,1,0,0,3,1},
	{1,0,1,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};
const int kMazeCannotExit[kMazeRows][kMazeCols] =
{
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,2,0,0,0,1,0,0,0,0,1,0,0,1,0,0,0,1,0,1},
	{1,1,1,1,0,1,0,1,1,0,1,0,1,1,0,1,0,1,0,1},
	{1,0,0,1,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,1},
	{1,0,1,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1},
	{1,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,1},
	{1,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,1,1,1,1},
	{1,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,3,1},
	{1,0,1,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};
// 미로 심볼 선언
// enum EMazeSymbol과 대응되는 배열이며, 둘 중 하나라도 변경하면 같이 변경해야 한다.
const char	kMazeSymbol[5] = { '.','#','S','E','P' };
// 랜덤 인카운터 확률. %단위이다. 
const int	kMazeEncounter = 10;
// 오류 출력용 문자열 배열
const char* kErrorString[6] =
{
	"Error: 미로를탈출할 수 없습니다.\n",
	"Error: 시작 위치가 없습니다.\n",
	"Error: 종료 위치가 없습니다.\n",
	"Error: 시작 위치가 여러개입니다.\n",
	"Error: 종료 위치가 여러개입니다.\n",
	"Error: 미로에 알 수 없는 값이 있습니다.\n",
};

// 플레이어 관련 선언
// 플레이어 최대 체력이다. 초기값으로도 쓴다.
const int	kPlayerMaxHP = 100;
// 플레이어 데미지 최대 최소값
const int	kPlayerAttackDamageMax = 15;
const int	kPlayerAttackDamageMin = 5;
// 플레이어 데미지 계산할 때 이용하는 값. rand 함수에 module 연산을 적용해 최소값에 더한다.
const int	kPlayerAttackDamageModular = kPlayerAttackDamageMax - kPlayerAttackDamageMin + 1;
// 플레이어 크리티컬 확률. %단위 이다.
const int	kPlayerCritRate = 10;
// 플레이어 크리티컬 배율. 크리티컬이 터졌을 때 데미지에 곱해 반환한다.
const int	kPlayerCritDamage = 2;

// 적 관련 설정.
// 적 최대 체력이다. 초기값으로도 쓴다.
const int	kEnemyMaxHP = 50;
// 적 데미지 최대 최소값
const int	kEnemyAttackDamageMax = 10;
const int	kEnemyAttackDamageMin = 5;
// 적 데미지 계산할 때 이용하는 값. rand 함수에 module 연산을 적용해 최소값에 더한다.
const int	kEnemyAttackDamageModular = kEnemyAttackDamageMax - kEnemyAttackDamageMin + 1;

// 함수 선언
void					Homework05_Run(void);
EMazeState				InitMazeSetting(int &PlayerX, int &PlayerY, int &EndX, int &EndY);
EMazeState				MazeSearchExit(int PosX, int PosY, bool Visited[kMazeRows][kMazeCols]);
void					PrintInformation(void);
void					GameLoop(int& PlayerX, int& PlayerY, int& EndX, int& EndY, int& PlayerHP);
void					PrintMaze(int PlayerX, int PlayerY, int PlayerHP);
EPlayerMoveDirection	PlayerMoveInput(int& PlayerX, int& PlayerY, int& PlayerHP);
void					PlayerPosUpdate(EPlayerMoveDirection PlayerMoveDirection, int& PlayerX, int& PlayerY);
void					PlayerFightEnemy(int &PlayerHP);

void	Homework05_Run(void)
{
	printf("Homework05_Run\n");
	// 쓸 변수들 설정
	int			PlayerX = -1;
	int			PlayerY = -1;
	int			EndX = -1;
	int			EndY = -1;
	int			PlayerHP = kPlayerMaxHP;
	// 플레이어 위치 종료 위치 초기화하며 미로에 오류가 있는지 없는지 확인하기
	EMazeState	MazeState = InitMazeSetting(PlayerX, PlayerY, EndX, EndY);

	// 오류가 있으면 오류 메시지를 출력하고 리턴한다.
	if (!MazeState || MazeState != MazeState_CanExit)
	{
		printf("%s", kErrorString[MazeState]);
		return ;
	}
	// 게임 시작하기 전 게임 설명
	PrintInformation();
	// 실제 게임 실행부
	GameLoop(PlayerX, PlayerY, EndX, EndY, PlayerHP);
	// 종료 후 플레이어 상태 확인
	if (PlayerHP)
	{
		PrintMaze(PlayerX, PlayerY, PlayerHP);
		printf("미로를 탈출하셨습니다!\n");
	}
	else
	{
		printf("사망하셨습니다...\n");
	}
}

// 미로 초기 설정 출력문
void	PrintInformation(void)
{
	printf("미로를 탈출하셔야 합니다.====================================================\n");
	printf("미로 정보\n");
	printf("	출력은 아래와 같습니다\n");
	printf("	길: [%c], 벽: [%c], 시작 위치: [%c], 종료 위치: [%c], 플레이어: [%c]\n",
		kMazeSymbol[MazeSymbol_Way], kMazeSymbol[MazeSymbol_Wall], kMazeSymbol[MazeSymbol_Start],
		kMazeSymbol[MazeSymbol_End], kMazeSymbol[MazeSymbol_Player]);
	printf("	플레이어 위치가 우선 출력됩니다.\n");
	printf("플레이어 정보\n");
	printf("	초기 HP는 [%d]입니다.\n", kPlayerMaxHP);
	printf("	HP가 [0]이 되면 사망합니다.\n");
	printf("	공격 데미지 최소값은 [%d], 최대값은 [%d]입니다.\n", kPlayerAttackDamageMin, kPlayerAttackDamageMax);
	printf("	크리티컬 확률은 [%d]%%이며 데미지가 [%d]배 들어갑니다.\n", kPlayerCritRate, kPlayerCritDamage);
	printf("적 정보\n");
	printf("	이동 시 [%d]%% 확률로 조우합니다.\n", kMazeEncounter);
	printf("	초기 HP는 [%d]입니다.\n", kEnemyMaxHP);
	printf("	공격 데미지 최소값은 [%d], 최대값은 [%d]입니다.\n", kEnemyAttackDamageMin, kEnemyAttackDamageMax);
	printf("살아서 탈출할 수 있길 기원합니다!\n");
	printf("==========================================================================\n\n");
}

// 게임 루프 함수
void	GameLoop(int& PlayerX, int& PlayerY, int& EndX, int& EndY, int& PlayerHP)
{
	while (PlayerHP && (PlayerX != EndX || PlayerY != EndY))
	{
		PrintMaze(PlayerX, PlayerY, PlayerHP);
		EPlayerMoveDirection PlayerMoveDirection = PlayerMoveInput(PlayerX, PlayerY, PlayerHP);
		PlayerPosUpdate(PlayerMoveDirection, PlayerX, PlayerY);
		int	EncounterCheck = rand() % 100;
		if (EncounterCheck < 10)
			PlayerFightEnemy(PlayerHP);
	}
}

// 미로 출력 함수. 플레이어 위치를 우선 출력한다.
void	PrintMaze(int PlayerX, int PlayerY, int PlayerHP)
{
	printf("미로\n");
	for (int MazeRowCount = 0; MazeRowCount < kMazeRows; MazeRowCount++)
	{
		for (int MazeColCount = 0; MazeColCount < kMazeCols; MazeColCount++)
		{
			if (MazeColCount == PlayerX && MazeRowCount == PlayerY)
			{
				printf("%c", kMazeSymbol[MazeSymbol_Player]);
			}
			else
			{
				printf("%c", kMazeSymbol[kMaze[MazeRowCount][MazeColCount]]);
			}
		}
		printf("\n");
	}
	// 미로 출력 이후 플레이어의 체력도 출력한다.
	printf("현재 플레이어 체력은 [%d]입니다.\n\n", PlayerHP);
}

// 미로 초기 설정 함수. 플레이어 위치와 종료 위치를 확인하고 미로에 오류가 있는지 확인한다.
EMazeState	InitMazeSetting(int& PlayerX, int& PlayerY, int& EndX, int& EndY)
{
	for (int MazeRowCount = 0; MazeRowCount < kMazeRows; MazeRowCount++)
	{
		for (int MazeColCount = 0; MazeColCount < kMazeCols; MazeColCount++)
		{
			if (kMaze[MazeRowCount][MazeColCount] == MazeSymbol_Start)
			{
				if (PlayerX >= 0 && PlayerY >= 0)
				{
					return (MazeState_DuplicateStart);
				}
				PlayerX = MazeColCount;
				PlayerY = MazeRowCount;
			}
			else if (kMaze[MazeRowCount][MazeColCount] == MazeSymbol_End)
			{
				if (EndX >= 0 && EndY >= 0)
				{
					return (MazeState_DuplicateEnd);
				}
				EndX = MazeColCount;
				EndY = MazeRowCount;
			}
			else if (kMaze[MazeRowCount][MazeColCount] != MazeSymbol_Way &&
				kMaze[MazeRowCount][MazeColCount] != MazeSymbol_Wall &&
				kMaze[MazeRowCount][MazeColCount] != MazeSymbol_Start &&
				kMaze[MazeRowCount][MazeColCount] != MazeSymbol_End)
				return (MazeState_UnknownSymbol);
		}
	}
	if (PlayerX == -1 || PlayerY == -1)
		return (MazeState_NoStart);
	if (EndX == -1 || EndY == -1)
		return (MazeState_NoEnd);
	bool Visited[kMazeRows][kMazeCols] = { {0, }, };
	return (MazeSearchExit(PlayerX, PlayerY, Visited));
}

// 플레이어가 나갈 수 있는지 없는지 확인하는 함수.
EMazeState	MazeSearchExit(int PosX, int PosY, bool Visited[kMazeRows][kMazeCols])
{
	if (PosX < 0 || PosX >= kMazeCols)
		return (MazeState_NoError);
	if (PosY < 0 || PosY >= kMazeRows)
		return (MazeState_NoError);
	if (Visited[PosY][PosX])
		return (MazeState_NoError);
	Visited[PosY][PosX] = true;
	if (kMaze[PosY][PosX] == MazeSymbol_Wall)
		return (MazeState_NoError);
	if (kMaze[PosY][PosX] == MazeSymbol_End)
		return (MazeState_CanExit);

	// 윗쪽 확인
	EMazeState	MoveToUp = MazeSearchExit(PosX, PosY - 1, Visited);
	if (MoveToUp)
		return (MoveToUp);
	// 아랫쪽 확인
	EMazeState	MoveToDown = MazeSearchExit(PosX, PosY + 1, Visited);
	if (MoveToDown)
		return (MoveToDown);
	// 왼쪽 확인
	EMazeState	MoveToLeft = MazeSearchExit(PosX - 1, PosY, Visited);
	if (MoveToLeft)
		return (MoveToLeft);
	// 오른쪽 확인
	EMazeState	MoveToRight = MazeSearchExit(PosX + 1, PosY, Visited);
	if (MoveToRight)
		return (MoveToRight);
	// 다 돌았는데 여기로 돌아온다는 것은 출구가 없다는 뜻이다.
	return (MazeState_NoError);
}

// 키보드 입력을 받아 움직일 위치를 반환한다.
EPlayerMoveDirection	PlayerMoveInput(int& PlayerX, int& PlayerY, int& PlayerHP)
{
	char	UserInput;

	printf("대소문자 구분 없이 아래 문자를 입력하면 이동할 수 있습니다.\n");
	printf("     W[↑]\n");
	printf("A[←] S[↓] D[→]\n");
	printf("이동하실 방향을 입력해주세요: ");
	std::cin >> UserInput;
	while ((UserInput != PlayerMoveInput_UpUpper && UserInput != PlayerMoveInput_UpLower) &&
		(UserInput != PlayerMoveInput_DownUpper && UserInput != PlayerMoveInput_DownLower) &&
		(UserInput != PlayerMoveInput_LeftUpper && UserInput != PlayerMoveInput_LeftLower) &&
		(UserInput != PlayerMoveInput_RightUpper && UserInput != PlayerMoveInput_RightLower))
	{
		printf("잘못 입력하셨습니다.\n");
		printf("     W[↑]\n");
		printf("A[←] S[↓] D[→]\n");
		printf("이동하실 방향을 입력해주세요: ");
		std::cin.clear();
		std::cin.ignore(10000, '\n');
		std::cin >> UserInput;		
	}
	if (UserInput == PlayerMoveInput_UpUpper || UserInput == PlayerMoveInput_UpLower)
	{
		return (PlayerMoveDirection_Up);
	}
	else if (UserInput == PlayerMoveInput_DownUpper || UserInput == PlayerMoveInput_DownLower)
	{
		return (PlayerMoveDirection_Down);

	}
	else if (UserInput == PlayerMoveInput_LeftUpper || UserInput == PlayerMoveInput_LeftLower)
	{
		return (PlayerMoveDirection_Left);
	}
	else
	{
		return (PlayerMoveDirection_Right);
	}
}

void	PlayerPosUpdate(EPlayerMoveDirection PlayerMoveDirection, int& PlayerX, int& PlayerY)
{
	switch (PlayerMoveDirection)
	{
	case (PlayerMoveDirection_Up):
	{
		if (PlayerY - 1 > 0 && PlayerY - 1 < kMazeRows && kMaze[PlayerY - 1][PlayerX] != MazeSymbol_Wall)
			PlayerY -= 1;
		break ;
	}
	case (PlayerMoveDirection_Left):
	{
		if (PlayerX - 1 > 0 && PlayerX - 1 < kMazeCols && kMaze[PlayerY][PlayerX - 1] != MazeSymbol_Wall)
			PlayerX -= 1;
		break;
	}
	case (PlayerMoveDirection_Down):
	{
		if (PlayerY + 1> 0 && PlayerY + 1 < kMazeRows && kMaze[PlayerY + 1][PlayerX] != MazeSymbol_Wall)
			PlayerY += 1;
		break;
	}
	case (PlayerMoveDirection_Right):
	{
		if (PlayerX + 1 > 0 && PlayerX + 1 < kMazeCols && kMaze[PlayerY][PlayerX + 1] != MazeSymbol_Wall)
			PlayerX += 1;
		break;
	}
	default:
	{
		printf("Error: PlayerPosUpdate에 알 수 없는 값이 인자로 들어왔습니다.\n");
	}
	}
}

// 인카운터시 적과 싸우는 함수.
void	PlayerFightEnemy(int& PlayerHP)
{
	int	EnemyHP = kEnemyMaxHP;
	int	Turn = 0;

	printf("적과 조우했습니다!\n");
	while (PlayerHP && EnemyHP)
	{
		if (!(Turn % 2))
		{
			int	PlayerAttack = kPlayerAttackDamageMin + rand() % kPlayerAttackDamageModular;
			int	PlayerCrit = rand() % 100;

			printf("%d번째 턴======================\n", Turn / 2 + 1);
			printf("현재 플레이어 체력:[%d]\n", PlayerHP);
			printf("현재 적 체력:[%d]\n", EnemyHP);
			if (PlayerCrit >= kPlayerCritRate)
			{
				printf("플레이어 공격\n플레이어가 %d 데미지를 넣었습니다.\n", PlayerAttack);
			}
			else
			{
				PlayerAttack *= kPlayerCritDamage;
				printf("★치명타★\n플레이어가 %d 데미지를 넣었습니다!\n", PlayerAttack);
			}
			EnemyHP -= PlayerAttack;
			EnemyHP = EnemyHP < 0 ? 0 : EnemyHP;
			printf("남은 적의 체력 [%d]\n", EnemyHP);
		}
		else
		{
			int	EnemyAttack = kEnemyAttackDamageMin + rand() % kEnemyAttackDamageModular;

			printf("적 공격\n적이 %d 데미지를 넣었습니다.\n", EnemyAttack);
			PlayerHP -= EnemyAttack;
			PlayerHP = PlayerHP < 0 ? 0 : PlayerHP;
			printf("남은 플레이어 체력 [%d]\n", PlayerHP);
			printf("===============================\n\n");
		}
		Turn++;
	}
	if ((Turn % 2))
		printf("===============================\n\n");
}
