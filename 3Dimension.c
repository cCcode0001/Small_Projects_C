#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <Windows.h>
#include <conio.h>

// (! ���ǻ��� !)
// * ������ ����� ǥ������ �ʴ´ٸ� Ctrl + ���콺 �� �� Console ȭ���� ��ҽ��Ѿ� �Ѵ�. *

// �𼭸� ���� ���
// �ʹ� ũ�� ȭ�鿡 �� ǥ������ �ʱ� ������ ������ ���ؿ��� ���� ����
#define SizeSide 15

// �ﰢ�Լ����� ���� ���� ���
#define PI 3.1415926

// ������ (0, 0) ���� �ٸ��� ���� ������ ���� ���� (���� ��꿡���� �ݿ� X)
// ��, ���� �̵��� �Ÿ��� �ǹ�
int Increa_Principle = SizeSide + (SizeSide / 2);

// ���� ��� ��ġ
COORD Pos = { 0, 0 };

// �� �ϳ��� ���� ������ ���� ����ü
struct PointPos {
	// x, y, z �� ��ǥ�� ������ �迭 ����
	// ��� ���·� ǥ��
	double Pos[3][1];
};

// Ŀ�� ������ �����ϴ� �Լ�
void CursorInfo();
// Ư�� ��ǥ�� ���� ����ϴ� �Լ�
void DrawPoint(int x, int y);
// DDA �˰������� ������ �׸��� �Լ�
void DDA(double x1, double y1, double x2, double y2);
// ȭ���� ����� �Լ�
void ClearScreen();

int main()
{
	CursorInfo();

	// ������ü�� �������� 8���̱� ������
	// 8���� ����ü ����
	struct PointPos P1 = { 0, };
	struct PointPos P2 = { 0, };
	struct PointPos P3 = { 0, };
	struct PointPos P4 = { 0, };

	struct PointPos P5 = { 0, };
	struct PointPos P6 = { 0, };
	struct PointPos P7 = { 0, };
	struct PointPos P8 = { 0, };

	// ��� ������ ������ ��, ������ (x, y, z) ��ǥ�� ������ �迭 ����
	// ������ Temp Storage ���� 
	double TempX[8] = { 0.0, };
	double TempY[8] = { 0.0, };
	double TempZ[8] = { 0.0, };

	// 2���� �簢���� ȸ����Ű�� �ڵ�
	// �� �� ���� �Ÿ��� �����ؼ� ���鿡 ���� ��ǥ �ο�
	/*P1.Pos[0][0] = 0;
	P1.Pos[1][0] = SizeSide;

	P2.Pos[0][0] = SizeSide;
	P2.Pos[1][0] = SizeSide;

	P3.Pos[0][0] = SizeSide;
	P3.Pos[1][0] = 0;

	P4.Pos[0][0] = 0;
	P4.Pos[1][0] = 0;

	// x��� y�� �ܼ� ���� ũ�� �� 2 : 1

	// ������ ��ǥ�� (0, 0) �� ����� ������ ��߳� �� �ֱ� ������
	// ���� �̵��� ������ ���Ŀ� �ݿ� X

	DDA(P4.Pos[0][0] + Increa_Principle, P4.Pos[1][0] + Increa_Principle, P3.Pos[0][0] + Increa_Principle, P3.Pos[1][0] + Increa_Principle);
	DDA(P3.Pos[0][0] + Increa_Principle, P3.Pos[1][0] + Increa_Principle, P2.Pos[0][0] + Increa_Principle, P2.Pos[1][0] + Increa_Principle);
	DDA(P4.Pos[0][0] + Increa_Principle, P4.Pos[1][0] + Increa_Principle, P1.Pos[0][0] + Increa_Principle, P1.Pos[1][0] + Increa_Principle);
	DDA(P1.Pos[0][0] + Increa_Principle, P1.Pos[1][0] + Increa_Principle, P2.Pos[0][0] + Increa_Principle, P2.Pos[1][0] + Increa_Principle);

	// ���� 1. �� P2 �� �� P1 ���� ���� �ϳ��� �� ��µȴ�.
	// �ذ�. DDA �˰��� ��� �κ� ����

	// ���� 2. �� P2 ���� �� P1 ���� ������ �մ� ���� ����� �� �ǵ��� �ݴ�� ��µȴ�.
	// �ذ�. DDA �˰��� ���밪 �κ� ����

	// ȸ���� �� ������ �Ǵ� ����
	int Seta = 30;

	// ������ ȸ���� ����ϴ� ������ ���ϸ� �ȵǴ� ���� ����
	// �ӽ� �迭 ������ ����
	TempX[0] = P1.Pos[0][0];
	TempX[1] = P2.Pos[0][0];
	TempX[2] = P3.Pos[0][0];
	TempX[3] = P4.Pos[0][0];

	TempY[0] = P1.Pos[1][0];
	TempY[1] = P2.Pos[1][0];
	TempY[2] = P3.Pos[1][0];
	TempY[3] = P4.Pos[1][0];

	// �ﰢ�Լ����� 60�й��� �Լ��� �Ű��� �ַ���
	// Seta(60�й� ����) * PI / 180 ���·� ��� �Ѵ�.

	// ���е��� ���ؼ� float ��� double �� ���
	while (Seta < 360)
	{
		// ȭ�� ������ ��Ű�� ����� �κ�
		Sleep(500);
		ClearScreen();

		// ȸ�� ��İ� ��ǥ ��� ���� ��İ��� ����ϴ� �κ�
		P1.Pos[0][0] = (cos(Seta * PI / 180) * TempX[0]) + (-sin(Seta * PI / 180) * TempY[0]);
		P1.Pos[1][0] = (sin(Seta * PI / 180) * TempX[0]) + (cos(Seta * PI / 180) * TempY[0]);

		P2.Pos[0][0] = (cos(Seta * PI / 180) * TempX[1]) + (-sin(Seta * PI / 180) * TempY[1]);
		P2.Pos[1][0] = (sin(Seta * PI / 180) * TempX[1]) + (cos(Seta * PI / 180) * TempY[1]);

		P3.Pos[0][0] = (cos(Seta * PI / 180) * TempX[2]) + (-sin(Seta * PI / 180) * TempY[2]);
		P3.Pos[1][0] = (sin(Seta * PI / 180) * TempX[2]) + (cos(Seta * PI / 180) * TempY[2]);

		P4.Pos[0][0] = (cos(Seta * PI / 180) * TempX[3]) + (-sin(Seta * PI / 180) * TempY[3]);
		P4.Pos[1][0] = (sin(Seta * PI / 180) * TempX[3]) + (cos(Seta * PI / 180) * TempY[3]);

		// ��� ����� ȭ�鿡 ����ϴ� �κ�
		DDA(P4.Pos[0][0] + Increa_Principle, P4.Pos[1][0] + Increa_Principle, P3.Pos[0][0] + Increa_Principle, P3.Pos[1][0] + Increa_Principle);
		DDA(P3.Pos[0][0] + Increa_Principle, P3.Pos[1][0] + Increa_Principle, P2.Pos[0][0] + Increa_Principle, P2.Pos[1][0] + Increa_Principle);
		DDA(P4.Pos[0][0] + Increa_Principle, P4.Pos[1][0] + Increa_Principle, P1.Pos[0][0] + Increa_Principle, P1.Pos[1][0] + Increa_Principle);
		DDA(P1.Pos[0][0] + Increa_Principle, P1.Pos[1][0] + Increa_Principle, P2.Pos[0][0] + Increa_Principle, P2.Pos[1][0] + Increa_Principle);

		// ������ ��� ��ȭ�� �༭ ������ �̵��� ǥ��
		Seta += 15;
	}*/

	// ���� 3. ������ ���� ���� ȸ����ų �� ������ �ְ�ȴ�.
	// �ذ�. ���� ���� ��Ƶδ� �������� ���� �������ν� �ذ� 
	// (Ư�� ������ �̵���Ų ���� ��� ������ �ٷ� �����ؼ� ���� ��꿡 ���Ǵ� ���� ������ �ƴ� (���� + Ư�� ����) �� �Ǿ� �ǵ��� ������ ������ �����.)

	// ���� 4. �밢���� �׸��� ���� ������ ���� �ٱ����� ������ ��찡 �����.
	// ���ذ�. �ֿܼ��� x��� y�� ������ 1 : 1 �� �������� �ʱ� ������ �߻��ϴ� ���ε�, �� �κп� ���ؼ��� ���Ŀ� �� ���

	// 3���� ������ü�� ȸ����Ű�� �ڵ�
	// �� �� ���� �Ÿ����� ������ ��ǥ�� �ο��ϴ� �κ�
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

	// ó�� ȭ�鿡 ����ϴ� �κ�
	DDA(P5.Pos[0][0] + Increa_Principle, P5.Pos[1][0] + Increa_Principle, P6.Pos[0][0] + Increa_Principle, P6.Pos[1][0] + Increa_Principle);
	DDA(P6.Pos[0][0] + Increa_Principle, P6.Pos[1][0] + Increa_Principle, P2.Pos[0][0] + Increa_Principle, P2.Pos[1][0] + Increa_Principle);
	DDA(P2.Pos[0][0] + Increa_Principle, P2.Pos[1][0] + Increa_Principle, P1.Pos[0][0] + Increa_Principle, P1.Pos[1][0] + Increa_Principle);
	DDA(P1.Pos[0][0] + Increa_Principle, P1.Pos[1][0] + Increa_Principle, P5.Pos[0][0] + Increa_Principle, P5.Pos[1][0] + Increa_Principle);

	// ȸ���� �߿��� ����� �� ���� ȸ�� ��(����)
	// x �� ȸ�� ��
	int Alpha = 0;
	// y �� ȸ�� ��
	int Beta = 0;
	// z �� ȸ�� ��
	int Gamma = 0;
	
	// ������ ������ ������ ���ϴ� Ű���� �Է°� ����
	char Input;

	// �� ���� ��ҵ��� �ӽ� ������ ����
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

	// �����̴� �� �����ϴ� Ű���� ������ ������ Ű�� �Է����� �� �����ϹǷ�
	// ���� �ݺ����� ���� ������ �������� �ʾҴ�.
	while (1)
	{
		Sleep(500);
		ClearScreen();

		// ������ �� ���Ǵ� Ű ���� ������ ���
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
		printf("- 3���� ���� ȸ�� ���α׷� -\n\n");
		printf("* Q, A Ű�� x �� ȸ���� ���\n");
		printf("* W, S Ű�� y �� ȸ���� ���\n");
		printf("* E, D Ű�� z �� ȸ���� ���\n");
		printf("Ps. �� �� ������ Ű�� ����\n");
		printf("\n\nMade by Jeong boil (cCcode)");

		// �� ������ ��ǥ ��Ŀ� 3���� ȸ�� ����� ���ϴ� �κ�
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

		// �� ���� ���� ���� (������ü�� ������ �� 12��)
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

		// ���� ���� ����ó�� ���� ������ �̾� ����ϴ� �κ�
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

		// - �� Ű�� ���� -
		// Q, A �� x �� ȸ��
		// W, S �� y �� ȸ��
		// E, D �� z �� ȸ��

		// Ű���尡 ������ ��
		if (_kbhit()) {
			// Ű���� ���� ���� ������ �ް�
			Input = _getch();

			// �� ���� ���� case �� �´� ������ ����
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
		// �Լ� Ư���� ��°� �Է��� �ʾ� ����� ����� �Ǵ��� Ȯ���ϰ� ���� �Է��� ����
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
