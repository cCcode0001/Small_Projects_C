#include <stdio.h>
#include <math.h>
#include <Windows.h> 

// 글자가 깨진다면, 해당 Conosle 의 크기가 그리려는 문자보다 작다는 의미이므로
// Ctral + 마우스 휠 을 통해 Console 화면을 축소하거나 
// 곡선의 크기 및 두께를 결정하는 변수인 Radius, Thickness 등을 수정

// 곡선이 그려지는 도중 곡선이 Console 화면 크기보다 커질 것 같아서 확대 하는 건 크게 문제 X, 축소가 문제 

// 반지름 상수 
#define Radius 15.0
// 두께 상수 (원의 방정식 오차 범위) 
#define Thickness 1.0

// 좌표 이동 함수 
void Gotoxy(int x, int y);
// 커서 정보 함수 
void CursorInfo();

int main()
{
	CursorInfo();
	printf("- 원을 이용해 부드러운 곡선을 그리는 프로그램 -\n");
	printf("Made by Jeong boil (cCcode)\n\n\n");
	
	printf("* Ctrl 키와 마우스 휠을 이용해 화면을 최대한 축소해주세요.\n");
	printf("p.s 문자가 깨질 수 있기 때문에, 프로그램이 실행되는 동안에 확대를 하시면 안됩니다.\n\n");
	printf("준비가 되셨다면 아무키나 눌러주세요");
	_getch();
	
	int i, j;
	// console 과 좌표 평면은 y 축 변화 방향이 다르기 때문에 좌표 평면처럼 연산할 변수 필요 
	double Xpos, Ypos = 0;
	
	// 곡선을 그릴 때
	// 1) 아래 곡선은 Ypos 의 초깃값을 0 으로 설정
	// 2) 위 곡선은 Ypos 의 초깃값을 Radius 로 설정, 반복 조건문의 목표 값을 Radius / 2 로 설정
	
	// 다음 반원을 그릴 시작 x 좌표는 
	// Radius * 2 + Radius * 2 이므로, 
	// 2(Radius + Radius)
	// 즉, (n 이 그린 원의 개수라 가정할 때)
	// next GotoX = n * (Radius + Radius) 
	
	// 원점을 포함한 원을 그리기 때문에 Radius * 2 + 1 번 반복
	// 다만, y 축의 경우 비율을 맞추기 위해 1 이 아니라 2 만큼 증가시켰기 때문에
	// Radius 번 반복해도 문제 X 
	
	// 출력 좌표 값들을 저장할 배열 변수들 
	int XPos_Sets[10000] = {0,};
	int YPos_Sets[10000] = {0,};
	// 배열 변수의 인덱스 값 
	int index = 0;
	
	// 원의 개수 변수 
	int CircleCnt = 0;
	// 출력 위치 변수들 
	int GotoX, GotoY = 0;
	
	int k;
	// 원을 그리는 과정을 활용해 곡선을 그릴 출력 좌표들을 얻는 부분 
	for (k = 0; k < 3; k++)
	{
		GotoX = CircleCnt * (Radius + Radius);
		GotoY = 0;
		Ypos = Radius;
		
		// 위로 볼록한 곡선 그리는 부분 
		for (i = 0; i <= Radius / 2; i++) 
		{
			Xpos = -Radius;
			GotoX = CircleCnt * (Radius + Radius); 
			for (j = 0; j <= Radius * 2; j++)
			{
				// Console 특성상 공백을 차지하는 비율이
				// 2x : y 이므로 비율을 맞추기 위해 y 축 추가 이동 
				
				if (sqrt(pow(Xpos, 2) + pow(Ypos, 2)) >= Radius - Thickness && sqrt(pow(Xpos, 2) + pow(Ypos, 2)) <= Radius + Thickness)
				{
					XPos_Sets[index] = GotoX + 4;
					YPos_Sets[index] = GotoY;
					
					index += 1;
				}		
	
				Xpos += 1;	
				GotoX += 1;
			}	
			// y 축 추가 이동 
			Ypos -= 2;
			GotoY += 1;
		}
		
		CircleCnt += 1;
		GotoX = CircleCnt * (Radius + Radius);
		GotoY = Radius / 2;
		Ypos = 0;
		
		// 아래로 볼록한 곡선 그리는 부분 
		for (i = 0; i <= Radius; i++) 
		{
			Xpos = -Radius;
			GotoX = CircleCnt * (Radius + Radius); 
			for (j = 0; j <= Radius * 2; j++)
			{
				if (sqrt(pow(Xpos, 2) + pow(Ypos, 2)) >= Radius - Thickness && sqrt(pow(Xpos, 2) + pow(Ypos, 2)) <= Radius + Thickness)
				{
					XPos_Sets[index] = GotoX + 4;
					YPos_Sets[index] = GotoY;
					
					index += 1;
				}		
	
				Xpos += 1;	
				GotoX += 1;
			}	
			// y 축 추가 이동 
			Ypos -= 2;
			GotoY += 1;
		}
		
		// 원의 개수 추가 
		CircleCnt += 1;
	}
	
	// 임시 저장 변수
	int temp = 0;
	// 요소의 개수를 파악하는 부분 
	int Count = 0;
	for (i = 0; XPos_Sets[i] != 0; i++)
		Count += 1; 
		
	// 곡선을 그리는 좌표들 간 크기 비교를 통해 곡선을 좌측부터 그리는 동작을 수행
	// - 정렬 조건 -
	// 1) x 가 작은 순서대로 (즉, x 값 기준 오름차순) 

	// x 와 y 를 동시 정렬하는 부분 (x 와 y 좌표는 변하면 안되는 순서쌍이므로) 
	for (i = 0; i < Count; i++)
	{
		for (j = 0; j < Count; j++)
		{
			if (XPos_Sets[j] > XPos_Sets[j + 1] && XPos_Sets[j + 1] != 0)
			{
				if (XPos_Sets[j] > XPos_Sets[j + 1])
				{
					temp = XPos_Sets[j];
					XPos_Sets[j] = XPos_Sets[j + 1];
					XPos_Sets[j + 1] = temp;
				
					temp = YPos_Sets[j];
					YPos_Sets[j] = YPos_Sets[j + 1];
					YPos_Sets[j + 1] = temp;	
				} 
			}
		}
	}
	
	// 실제 곡선을 출력하는 부분 
	for (i = 0; i < Count; i++)
	{
		Gotoxy(XPos_Sets[i], YPos_Sets[i] + Radius);
		Sleep(30); 
		printf("*");
	} 

	// 함수 곡선을 그릴 때 사용 될 원 코드 
	
	// 원점 (0, 0)을 기준으로 그리는 원의 방정식
	// x^2 + y^2 = r^2
	// √(x^2 + y^2) = r
	
	/*Ypos = Radius;
	for (i = 0; i <= Radius; i++) 
	{
		Xpos = -Radius;
		GotoX = CircleCnt * (Radius + Radius); 
		for (j = 0; j <= Radius * 2; j++)
		{
			if (sqrt(pow(Xpos, 2) + pow(Ypos, 2)) >= Radius - Thickness && sqrt(pow(Xpos, 2) + pow(Ypos, 2)) <= Radius + Thickness)
			{
				Gotoxy(GotoX, GotoY);
				printf("*");
			}		
			else
				printf(" ");
			Xpos += 1;	
			GotoX += 1;
		}
		printf("\n");
		
		Ypos -= 2;
		GotoY += 1;
	}*/
	 
	return 0;
}

void Gotoxy(int x, int y)
{
	COORD Pos = {x, y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void CursorInfo()
{
	CONSOLE_CURSOR_INFO Cursor = {0,};
	// 커서 굵기 
	Cursor.dwSize = 1;
	// 커서 보임 여부 
	Cursor.bVisible = FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Cursor);
}
