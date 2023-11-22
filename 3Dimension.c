#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <Windows.h>
#include <conio.h>

// (! 주의사항 !)
// * 도형이 제대로 표현되지 않는다면 Ctrl + 마우스 휠 로 Console 화면을 축소시켜야 한다. *

// 모서리 길이 상수
// 너무 크면 화면에 잘 표현되지 않기 때문에 적절한 수준에서 변경 가능
#define SizeSide 15

// 삼각함수에서 쓰는 파이 상수
#define PI 3.1415926

// 기준점 (0, 0) 에서 다르게 잡은 기준점 사이 차이 (실제 계산에서는 반영 X)
// 즉, 평행 이동할 거리를 의미
int Increa_Principle = SizeSide + (SizeSide / 2);

// 정보 출력 위치
COORD Pos = { 0, 0 };

// 점 하나가 가질 정보를 담은 구조체
struct PointPos {
	// x, y, z 축 좌표를 가지는 배열 변수
	// 행렬 형태로 표현
	double Pos[3][1];
};

// 커서 정보를 수정하는 함수
void CursorInfo();
// 특정 좌표에 점을 출력하는 함수
void DrawPoint(int x, int y);
// DDA 알고리즘으로 선분을 그리는 함수
void DDA(double x1, double y1, double x2, double y2);
// 화면을 지우는 함수
void ClearScreen();

int main()
{
	CursorInfo();

	// 정육면체의 꼭짓점은 8개이기 때문에
	// 8개의 구조체 선언
	struct PointPos P1 = { 0, };
	struct PointPos P2 = { 0, };
	struct PointPos P3 = { 0, };
	struct PointPos P4 = { 0, };

	struct PointPos P5 = { 0, };
	struct PointPos P6 = { 0, };
	struct PointPos P7 = { 0, };
	struct PointPos P8 = { 0, };

	// 행렬 연산을 수행할 때, 원래의 (x, y, z) 좌표를 저장할 배열 변수
	// 일종의 Temp Storage 역할 
	double TempX[8] = { 0.0, };
	double TempY[8] = { 0.0, };
	double TempZ[8] = { 0.0, };

	// 2차원 사각형을 회전시키는 코드
	// 각 점 사이 거리를 감안해서 점들에 개별 좌표 부여
	/*P1.Pos[0][0] = 0;
	P1.Pos[1][0] = SizeSide;

	P2.Pos[0][0] = SizeSide;
	P2.Pos[1][0] = SizeSide;

	P3.Pos[0][0] = SizeSide;
	P3.Pos[1][0] = 0;

	P4.Pos[0][0] = 0;
	P4.Pos[1][0] = 0;

	// x축과 y축 콘솔 단위 크기 비가 2 : 1

	// 기준점 좌표가 (0, 0) 을 벗어나면 공식이 어긋날 수 있기 때문에
	// 평행 이동한 정도는 수식에 반영 X

	DDA(P4.Pos[0][0] + Increa_Principle, P4.Pos[1][0] + Increa_Principle, P3.Pos[0][0] + Increa_Principle, P3.Pos[1][0] + Increa_Principle);
	DDA(P3.Pos[0][0] + Increa_Principle, P3.Pos[1][0] + Increa_Principle, P2.Pos[0][0] + Increa_Principle, P2.Pos[1][0] + Increa_Principle);
	DDA(P4.Pos[0][0] + Increa_Principle, P4.Pos[1][0] + Increa_Principle, P1.Pos[0][0] + Increa_Principle, P1.Pos[1][0] + Increa_Principle);
	DDA(P1.Pos[0][0] + Increa_Principle, P1.Pos[1][0] + Increa_Principle, P2.Pos[0][0] + Increa_Principle, P2.Pos[1][0] + Increa_Principle);

	// 문제 1. 점 P2 와 점 P1 사이 점이 하나가 덜 출력된다.
	// 해결. DDA 알고리즘 출력 부분 수정

	// 문제 2. 점 P2 에서 점 P1 으로 선분을 잇는 점을 출력할 때 의도와 반대로 출력된다.
	// 해결. DDA 알고리즘 절대값 부분 수정

	// 회전할 때 기준이 되는 각도
	int Seta = 30;

	// 도형의 회전을 출력하는 과정에 변하면 안되는 원본 값을
	// 임시 배열 변수에 저장
	TempX[0] = P1.Pos[0][0];
	TempX[1] = P2.Pos[0][0];
	TempX[2] = P3.Pos[0][0];
	TempX[3] = P4.Pos[0][0];

	TempY[0] = P1.Pos[1][0];
	TempY[1] = P2.Pos[1][0];
	TempY[2] = P3.Pos[1][0];
	TempY[3] = P4.Pos[1][0];

	// 삼각함수에서 60분법을 함수의 매개로 주려면
	// Seta(60분법 형태) * PI / 180 형태로 줘야 한다.

	// 정밀도를 위해서 float 대신 double 형 사용
	while (Seta < 360)
	{
		// 화면 딜레이 시키고 지우는 부분
		Sleep(500);
		ClearScreen();

		// 회전 행렬과 좌표 행렬 사이 행렬곱을 계산하는 부분
		P1.Pos[0][0] = (cos(Seta * PI / 180) * TempX[0]) + (-sin(Seta * PI / 180) * TempY[0]);
		P1.Pos[1][0] = (sin(Seta * PI / 180) * TempX[0]) + (cos(Seta * PI / 180) * TempY[0]);

		P2.Pos[0][0] = (cos(Seta * PI / 180) * TempX[1]) + (-sin(Seta * PI / 180) * TempY[1]);
		P2.Pos[1][0] = (sin(Seta * PI / 180) * TempX[1]) + (cos(Seta * PI / 180) * TempY[1]);

		P3.Pos[0][0] = (cos(Seta * PI / 180) * TempX[2]) + (-sin(Seta * PI / 180) * TempY[2]);
		P3.Pos[1][0] = (sin(Seta * PI / 180) * TempX[2]) + (cos(Seta * PI / 180) * TempY[2]);

		P4.Pos[0][0] = (cos(Seta * PI / 180) * TempX[3]) + (-sin(Seta * PI / 180) * TempY[3]);
		P4.Pos[1][0] = (sin(Seta * PI / 180) * TempX[3]) + (cos(Seta * PI / 180) * TempY[3]);

		// 계산 결과를 화면에 출력하는 부분
		DDA(P4.Pos[0][0] + Increa_Principle, P4.Pos[1][0] + Increa_Principle, P3.Pos[0][0] + Increa_Principle, P3.Pos[1][0] + Increa_Principle);
		DDA(P3.Pos[0][0] + Increa_Principle, P3.Pos[1][0] + Increa_Principle, P2.Pos[0][0] + Increa_Principle, P2.Pos[1][0] + Increa_Principle);
		DDA(P4.Pos[0][0] + Increa_Principle, P4.Pos[1][0] + Increa_Principle, P1.Pos[0][0] + Increa_Principle, P1.Pos[1][0] + Increa_Principle);
		DDA(P1.Pos[0][0] + Increa_Principle, P1.Pos[1][0] + Increa_Principle, P2.Pos[0][0] + Increa_Principle, P2.Pos[1][0] + Increa_Principle);

		// 각도에 계속 변화를 줘서 도형의 이동을 표현
		Seta += 15;
	}*/

	// 문제 3. 도형을 원점 기준 회전시킬 때 점들이 왜곡된다.
	// 해결. 원본 값만 담아두는 변수들을 따로 만듬으로써 해결 
	// (특정 각도를 이동시킨 값을 출력 변수에 바로 대입해서 다음 계산에 사용되는 값이 원본이 아닌 (원본 + 특정 각도) 가 되어 의도와 계산사이 오차가 생겼다.)

	// 문제 4. 대각선을 그리는 도중 선분이 도형 바깥으로 나오는 경우가 생긴다.
	// 미해결. 콘솔에서 x축과 y축 비율이 1 : 1 로 성립하지 않기 때문에 발생하는 것인데, 이 부분에 관해서는 추후에 더 고민

	// 3차원 정육면체를 회전시키는 코드
	// 각 점 사이 거리들을 감안해 좌표를 부여하는 부분
	P1.Pos[0][0] = SizeSide;
	P1.Pos[1][0] = 0;
	P1.Pos[2][0] = SizeSide;

	P2.Pos[0][0] = SizeSide;
	P2.Pos[1][0] = SizeSide;
	P2.Pos[2][0] = SizeSide;

	P3.Pos[0][0] = SizeSide;
	P3.Pos[1][0] = SizeSide;
	P3.Pos[2][0] = 0;

	P4.Pos[0][0] = SizeSide;
	P4.Pos[1][0] = 0;
	P4.Pos[2][0] = 0;

	P5.Pos[0][0] = 0;
	P5.Pos[1][0] = 0;
	P5.Pos[2][0] = SizeSide;

	P6.Pos[0][0] = 0;
	P6.Pos[1][0] = SizeSide;
	P6.Pos[2][0] = SizeSide;

	P7.Pos[0][0] = 0;
	P7.Pos[1][0] = SizeSide;
	P7.Pos[2][0] = 0;

	P8.Pos[0][0] = 0;
	P8.Pos[1][0] = 0;
	P8.Pos[2][0] = 0;

	// 처음 화면에 출력하는 부분
	DDA(P5.Pos[0][0] + Increa_Principle, P5.Pos[1][0] + Increa_Principle, P6.Pos[0][0] + Increa_Principle, P6.Pos[1][0] + Increa_Principle);
	DDA(P6.Pos[0][0] + Increa_Principle, P6.Pos[1][0] + Increa_Principle, P2.Pos[0][0] + Increa_Principle, P2.Pos[1][0] + Increa_Principle);
	DDA(P2.Pos[0][0] + Increa_Principle, P2.Pos[1][0] + Increa_Principle, P1.Pos[0][0] + Increa_Principle, P1.Pos[1][0] + Increa_Principle);
	DDA(P1.Pos[0][0] + Increa_Principle, P1.Pos[1][0] + Increa_Principle, P5.Pos[0][0] + Increa_Principle, P5.Pos[1][0] + Increa_Principle);

	// 회전에 중요한 요소인 각 축의 회전 값(각도)
	// x 축 회전 각
	int Alpha = 0;
	// y 축 회전 각
	int Beta = 0;
	// z 축 회전 각
	int Gamma = 0;
	
	// 도형의 움직일 방향을 정하는 키보드 입력값 변수
	char Input;

	// 각 원본 요소들을 임시 변수에 저장
	TempX[0] = P1.Pos[0][0];
	TempX[1] = P2.Pos[0][0];
	TempX[2] = P3.Pos[0][0];
	TempX[3] = P4.Pos[0][0];
	TempX[4] = P5.Pos[0][0];
	TempX[5] = P6.Pos[0][0];
	TempX[6] = P7.Pos[0][0];
	TempX[7] = P8.Pos[0][0];

	TempY[0] = P1.Pos[1][0];
	TempY[1] = P2.Pos[1][0];
	TempY[2] = P3.Pos[1][0];
	TempY[3] = P4.Pos[1][0];
	TempY[4] = P5.Pos[1][0];
	TempY[5] = P6.Pos[1][0];
	TempY[6] = P7.Pos[1][0];
	TempY[7] = P8.Pos[1][0];

	TempZ[0] = P1.Pos[2][0];
	TempZ[1] = P2.Pos[2][0];
	TempZ[2] = P3.Pos[2][0];
	TempZ[3] = P4.Pos[2][0];
	TempZ[4] = P5.Pos[2][0];
	TempZ[5] = P6.Pos[2][0];
	TempZ[6] = P7.Pos[2][0];
	TempZ[7] = P8.Pos[2][0];

	// 움직이는 데 관여하는 키들을 제외한 나머지 키들 입력했을 때 종료하므로
	// 따로 반복문의 종료 조건은 설정하지 않았다.
	while (1)
	{
		Sleep(500);
		ClearScreen();

		// 움직일 때 사용되는 키 등의 정보를 출력
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
		printf("- 3차원 도형 회전 프로그램 -\n\n");
		printf("* Q, A 키는 x 축 회전을 담당\n");
		printf("* W, S 키는 y 축 회전을 담당\n");
		printf("* E, D 키는 z 축 회전을 담당\n");
		printf("Ps. 그 외 나머지 키는 종료\n");
		printf("\n\nMade by Jeong boil (cCcode)");

		// 각 점들의 좌표 행렬에 3차원 회전 행렬을 곱하는 부분
		P1.Pos[0][0] = (cos(Alpha * PI / 180) * cos(Beta * PI / 180) * TempX[0]) + ((cos(Alpha * PI / 180) * sin(Beta * PI / 180) * sin(Gamma * PI / 180) - sin(Alpha * PI / 180) * cos(Gamma * PI / 180)) * TempY[0]) + ((cos(Alpha * PI / 180) * sin(Beta * PI / 180) * cos(Gamma * PI / 180) + sin(Alpha * PI / 180) * sin(Gamma * PI / 180)) * TempZ[0]);
		P1.Pos[1][0] = (sin(Alpha * PI / 180) * cos(Beta * PI / 180) * TempX[0]) + ((sin(Alpha * PI / 180) * sin(Beta * PI / 180) * sin(Gamma * PI / 180) + cos(Alpha * PI / 180) * cos(Gamma * PI / 180)) * TempY[0]) + ((sin(Alpha * PI / 180) * sin(Beta * PI / 180) * cos(Gamma * PI / 180) - cos(Alpha * PI / 180) * sin(Gamma * PI / 180)) * TempZ[0]);
		P1.Pos[2][0] = -sin(Beta * PI / 180) * TempX[0] + cos(Beta * PI / 180) * sin(Gamma * PI / 180) * TempY[0] + cos(Beta * PI / 180) * cos(Gamma * PI / 180) * TempZ[0];

		P2.Pos[0][0] = (cos(Alpha * PI / 180) * cos(Beta * PI / 180) * TempX[1]) + ((cos(Alpha * PI / 180) * sin(Beta * PI / 180) * sin(Gamma * PI / 180) - sin(Alpha * PI / 180) * cos(Gamma * PI / 180)) * TempY[1]) + ((cos(Alpha * PI / 180) * sin(Beta * PI / 180) * cos(Gamma * PI / 180) + sin(Alpha * PI / 180) * sin(Gamma * PI / 180)) * TempZ[1]);
		P2.Pos[1][0] = (sin(Alpha * PI / 180) * cos(Beta * PI / 180) * TempX[1]) + ((sin(Alpha * PI / 180) * sin(Beta * PI / 180) * sin(Gamma * PI / 180) + cos(Alpha * PI / 180) * cos(Gamma * PI / 180)) * TempY[1]) + ((sin(Alpha * PI / 180) * sin(Beta * PI / 180) * cos(Gamma * PI / 180) - cos(Alpha * PI / 180) * sin(Gamma * PI / 180)) * TempZ[1]);
		P2.Pos[2][0] = -sin(Beta * PI / 180) * TempX[1] + cos(Beta * PI / 180) * sin(Gamma * PI / 180) * TempY[1] + cos(Beta * PI / 180) * cos(Gamma * PI / 180) * TempZ[1];

		P3.Pos[0][0] = (cos(Alpha * PI / 180) * cos(Beta * PI / 180) * TempX[2]) + ((cos(Alpha * PI / 180) * sin(Beta * PI / 180) * sin(Gamma * PI / 180) - sin(Alpha * PI / 180) * cos(Gamma * PI / 180)) * TempY[2]) + ((cos(Alpha * PI / 180) * sin(Beta * PI / 180) * cos(Gamma * PI / 180) + sin(Alpha * PI / 180) * sin(Gamma * PI / 180)) * TempZ[2]);
		P3.Pos[1][0] = (sin(Alpha * PI / 180) * cos(Beta * PI / 180) * TempX[2]) + ((sin(Alpha * PI / 180) * sin(Beta * PI / 180) * sin(Gamma * PI / 180) + cos(Alpha * PI / 180) * cos(Gamma * PI / 180)) * TempY[2]) + ((sin(Alpha * PI / 180) * sin(Beta * PI / 180) * cos(Gamma * PI / 180) - cos(Alpha * PI / 180) * sin(Gamma * PI / 180)) * TempZ[2]);
		P3.Pos[2][0] = -sin(Beta * PI / 180) * TempX[2] + cos(Beta * PI / 180) * sin(Gamma * PI / 180) * TempY[2] + cos(Beta * PI / 180) * cos(Gamma * PI / 180) * TempZ[2];

		P4.Pos[0][0] = (cos(Alpha * PI / 180) * cos(Beta * PI / 180) * TempX[3]) + ((cos(Alpha * PI / 180) * sin(Beta * PI / 180) * sin(Gamma * PI / 180) - sin(Alpha * PI / 180) * cos(Gamma * PI / 180)) * TempY[3]) + ((cos(Alpha * PI / 180) * sin(Beta * PI / 180) * cos(Gamma * PI / 180) + sin(Alpha * PI / 180) * sin(Gamma * PI / 180)) * TempZ[3]);
		P4.Pos[1][0] = (sin(Alpha * PI / 180) * cos(Beta * PI / 180) * TempX[3]) + ((sin(Alpha * PI / 180) * sin(Beta * PI / 180) * sin(Gamma * PI / 180) + cos(Alpha * PI / 180) * cos(Gamma * PI / 180)) * TempY[3]) + ((sin(Alpha * PI / 180) * sin(Beta * PI / 180) * cos(Gamma * PI / 180) - cos(Alpha * PI / 180) * sin(Gamma * PI / 180)) * TempZ[3]);
		P4.Pos[2][0] = -sin(Beta * PI / 180) * TempX[3] + cos(Beta * PI / 180) * sin(Gamma * PI / 180) * TempY[3] + cos(Beta * PI / 180) * cos(Gamma * PI / 180) * TempZ[3];

		P5.Pos[0][0] = (cos(Alpha * PI / 180) * cos(Beta * PI / 180) * TempX[4]) + ((cos(Alpha * PI / 180) * sin(Beta * PI / 180) * sin(Gamma * PI / 180) - sin(Alpha * PI / 180) * cos(Gamma * PI / 180)) * TempY[4]) + ((cos(Alpha * PI / 180) * sin(Beta * PI / 180) * cos(Gamma * PI / 180) + sin(Alpha * PI / 180) * sin(Gamma * PI / 180)) * TempZ[4]);
		P5.Pos[1][0] = (sin(Alpha * PI / 180) * cos(Beta * PI / 180) * TempX[4]) + ((sin(Alpha * PI / 180) * sin(Beta * PI / 180) * sin(Gamma * PI / 180) + cos(Alpha * PI / 180) * cos(Gamma * PI / 180)) * TempY[4]) + ((sin(Alpha * PI / 180) * sin(Beta * PI / 180) * cos(Gamma * PI / 180) - cos(Alpha * PI / 180) * sin(Gamma * PI / 180)) * TempZ[4]);
		P5.Pos[2][0] = -sin(Beta * PI / 180) * TempX[4] + cos(Beta * PI / 180) * sin(Gamma * PI / 180) * TempY[4] + cos(Beta * PI / 180) * cos(Gamma * PI / 180) * TempZ[4];

		P6.Pos[0][0] = (cos(Alpha * PI / 180) * cos(Beta * PI / 180) * TempX[5]) + ((cos(Alpha * PI / 180) * sin(Beta * PI / 180) * sin(Gamma * PI / 180) - sin(Alpha * PI / 180) * cos(Gamma * PI / 180)) * TempY[5]) + ((cos(Alpha * PI / 180) * sin(Beta * PI / 180) * cos(Gamma * PI / 180) + sin(Alpha * PI / 180) * sin(Gamma * PI / 180)) * TempZ[5]);
		P6.Pos[1][0] = (sin(Alpha * PI / 180) * cos(Beta * PI / 180) * TempX[5]) + ((sin(Alpha * PI / 180) * sin(Beta * PI / 180) * sin(Gamma * PI / 180) + cos(Alpha * PI / 180) * cos(Gamma * PI / 180)) * TempY[5]) + ((sin(Alpha * PI / 180) * sin(Beta * PI / 180) * cos(Gamma * PI / 180) - cos(Alpha * PI / 180) * sin(Gamma * PI / 180)) * TempZ[5]);
		P6.Pos[2][0] = -sin(Beta * PI / 180) * TempX[5] + cos(Beta * PI / 180) * sin(Gamma * PI / 180) * TempY[5] + cos(Beta * PI / 180) * cos(Gamma * PI / 180) * TempZ[5];

		P7.Pos[0][0] = (cos(Alpha * PI / 180) * cos(Beta * PI / 180) * TempX[6]) + ((cos(Alpha * PI / 180) * sin(Beta * PI / 180) * sin(Gamma * PI / 180) - sin(Alpha * PI / 180) * cos(Gamma * PI / 180)) * TempY[6]) + ((cos(Alpha * PI / 180) * sin(Beta * PI / 180) * cos(Gamma * PI / 180) + sin(Alpha * PI / 180) * sin(Gamma * PI / 180)) * TempZ[6]);
		P7.Pos[1][0] = (sin(Alpha * PI / 180) * cos(Beta * PI / 180) * TempX[6]) + ((sin(Alpha * PI / 180) * sin(Beta * PI / 180) * sin(Gamma * PI / 180) + cos(Alpha * PI / 180) * cos(Gamma * PI / 180)) * TempY[6]) + ((sin(Alpha * PI / 180) * sin(Beta * PI / 180) * cos(Gamma * PI / 180) - cos(Alpha * PI / 180) * sin(Gamma * PI / 180)) * TempZ[6]);
		P7.Pos[2][0] = -sin(Beta * PI / 180) * TempX[6] + cos(Beta * PI / 180) * sin(Gamma * PI / 180) * TempY[6] + cos(Beta * PI / 180) * cos(Gamma * PI / 180) * TempZ[6];

		P8.Pos[0][0] = (cos(Alpha * PI / 180) * cos(Beta * PI / 180) * TempX[7]) + ((cos(Alpha * PI / 180) * sin(Beta * PI / 180) * sin(Gamma * PI / 180) - sin(Alpha * PI / 180) * cos(Gamma * PI / 180)) * TempY[7]) + ((cos(Alpha * PI / 180) * sin(Beta * PI / 180) * cos(Gamma * PI / 180) + sin(Alpha * PI / 180) * sin(Gamma * PI / 180)) * TempZ[7]);
		P8.Pos[1][0] = (sin(Alpha * PI / 180) * cos(Beta * PI / 180) * TempX[7]) + ((sin(Alpha * PI / 180) * sin(Beta * PI / 180) * sin(Gamma * PI / 180) + cos(Alpha * PI / 180) * cos(Gamma * PI / 180)) * TempY[7]) + ((sin(Alpha * PI / 180) * sin(Beta * PI / 180) * cos(Gamma * PI / 180) - cos(Alpha * PI / 180) * sin(Gamma * PI / 180)) * TempZ[7]);
		P8.Pos[2][0] = -sin(Beta * PI / 180) * TempX[7] + cos(Beta * PI / 180) * sin(Gamma * PI / 180) * TempY[7] + cos(Beta * PI / 180) * cos(Gamma * PI / 180) * TempZ[7];

		// 각 점의 선분 연결 (정육면체의 선분은 총 12개)
		// 1 - 2
		// 2 - 3
		// 3 - 4
		// 4 - 1

		// 5 - 6
		// 6 - 7
		// 7 - 8
		// 8 - 5

		// 1 - 5
		// 2 - 6
		// 3 - 7
		// 4 - 8

		// 위에 적힌 예시처럼 점과 점들을 이어 출력하는 부분
		DDA(P1.Pos[0][0] + Increa_Principle, P1.Pos[1][0] + Increa_Principle, P2.Pos[0][0] + Increa_Principle, P2.Pos[1][0] + Increa_Principle);
		DDA(P2.Pos[0][0] + Increa_Principle, P2.Pos[1][0] + Increa_Principle, P3.Pos[0][0] + Increa_Principle, P3.Pos[1][0] + Increa_Principle);
		DDA(P3.Pos[0][0] + Increa_Principle, P3.Pos[1][0] + Increa_Principle, P4.Pos[0][0] + Increa_Principle, P4.Pos[1][0] + Increa_Principle);
		DDA(P4.Pos[0][0] + Increa_Principle, P4.Pos[1][0] + Increa_Principle, P1.Pos[0][0] + Increa_Principle, P1.Pos[1][0] + Increa_Principle);

		DDA(P5.Pos[0][0] + Increa_Principle, P5.Pos[1][0] + Increa_Principle, P6.Pos[0][0] + Increa_Principle, P6.Pos[1][0] + Increa_Principle);
		DDA(P6.Pos[0][0] + Increa_Principle, P6.Pos[1][0] + Increa_Principle, P7.Pos[0][0] + Increa_Principle, P7.Pos[1][0] + Increa_Principle);
		DDA(P7.Pos[0][0] + Increa_Principle, P7.Pos[1][0] + Increa_Principle, P8.Pos[0][0] + Increa_Principle, P8.Pos[1][0] + Increa_Principle);
		DDA(P8.Pos[0][0] + Increa_Principle, P8.Pos[1][0] + Increa_Principle, P5.Pos[0][0] + Increa_Principle, P5.Pos[1][0] + Increa_Principle);

		DDA(P1.Pos[0][0] + Increa_Principle, P1.Pos[1][0] + Increa_Principle, P5.Pos[0][0] + Increa_Principle, P5.Pos[1][0] + Increa_Principle);
		DDA(P2.Pos[0][0] + Increa_Principle, P2.Pos[1][0] + Increa_Principle, P6.Pos[0][0] + Increa_Principle, P6.Pos[1][0] + Increa_Principle);
		DDA(P3.Pos[0][0] + Increa_Principle, P3.Pos[1][0] + Increa_Principle, P7.Pos[0][0] + Increa_Principle, P7.Pos[1][0] + Increa_Principle);
		DDA(P4.Pos[0][0] + Increa_Principle, P4.Pos[1][0] + Increa_Principle, P8.Pos[0][0] + Increa_Principle, P8.Pos[1][0] + Increa_Principle);

		// - 각 키의 역할 -
		// Q, A 가 x 축 회전
		// W, S 가 y 축 회전
		// E, D 가 z 축 회전

		// 키보드가 눌렸을 때
		if (_kbhit()) {
			// 키보드 눌린 값을 변수로 받고
			Input = _getch();

			// 그 값에 따라 case 에 맞는 동작을 수행
			switch (Input)
			{
			case 'q': Alpha += 10;
				break;
			case 'a': Alpha -= 10;
				break;
			case 'w': Beta += 10;
				break;
			case 's': Beta -= 10;
				break;
			case 'e': Gamma += 10;
				break;
			case 'd': Gamma -= 10;
				break;
			default: return 0;
			}
		}
		// 함수 특성상 출력과 입력이 늦어 출력이 제대로 되는지 확인하고 다음 입력을 수행
	}

	return 0;
}

void CursorInfo()
{
	CONSOLE_CURSOR_INFO Cursor = { 0, };
	Cursor.dwSize = 1;
	Cursor.bVisible = FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Cursor);
}

void DrawPoint(int x, int y)
{
	COORD Pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);

	printf("**");
}

void DDA(double x1, double y1, double x2, double y2)
{
	double dx = x2 - x1;
	double dy = y2 - y1;

	double PointCnt;

	if (fabs(dx) > fabs(dy))
		PointCnt = fabs(dx);
	else
		PointCnt = fabs(dy);

	double x = x1;
	double y = y1;

	double IncreaseX = dx / PointCnt;
	double IncreaseY = dy / PointCnt;

	DrawPoint(round(x), round(y));

	int i;
	for (i = 0; i < PointCnt; i++)
	{
		x += IncreaseX;
		y += IncreaseY;
		DrawPoint(round(x), round(y));
	}
}

void ClearScreen()
{
	COORD Pos = { 0,0 };
	DWORD dw;
	FillConsoleOutputCharacter(GetStdHandle(STD_OUTPUT_HANDLE), ' ', 1000 * 1000, Pos, &dw);
}
