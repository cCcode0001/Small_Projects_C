#include <stdio.h>
#include <math.h>
#include <Windows.h> 

// ���ڰ� �����ٸ�, �ش� Conosle �� ũ�Ⱑ �׸����� ���ں��� �۴ٴ� �ǹ��̹Ƿ�
// Ctral + ���콺 �� �� ���� Console ȭ���� ����ϰų� 
// ��� ũ�� �� �β��� �����ϴ� ������ Radius, Thickness ���� ����

// ��� �׷����� ���� ��� Console ȭ�� ũ�⺸�� Ŀ�� �� ���Ƽ� Ȯ�� �ϴ� �� ũ�� ���� X, ��Ұ� ���� 

// ������ ��� 
#define Radius 15.0
// �β� ��� (���� ������ ���� ����) 
#define Thickness 1.0

// ��ǥ �̵� �Լ� 
void Gotoxy(int x, int y);
// Ŀ�� ���� �Լ� 
void CursorInfo();

int main()
{
	CursorInfo();
	printf("- ���� �̿��� �ε巯�� ��� �׸��� ���α׷� -\n");
	printf("Made by Jeong boil (cCcode)\n\n\n");
	
	printf("* Ctrl Ű�� ���콺 ���� �̿��� ȭ���� �ִ��� ������ּ���.\n");
	printf("p.s ���ڰ� ���� �� �ֱ� ������, ���α׷��� ����Ǵ� ���ȿ� Ȯ�븦 �Ͻø� �ȵ˴ϴ�.\n\n");
	printf("�غ� �Ǽ̴ٸ� �ƹ�Ű�� �����ּ���");
	_getch();
	
	int i, j;
	// console �� ��ǥ ����� y �� ��ȭ ������ �ٸ��� ������ ��ǥ ���ó�� ������ ���� �ʿ� 
	double Xpos, Ypos = 0;
	
	// ��� �׸� ��
	// 1) �Ʒ� ��� Ypos �� �ʱ갪�� 0 ���� ����
	// 2) �� ��� Ypos �� �ʱ갪�� Radius �� ����, �ݺ� ���ǹ��� ��ǥ ���� Radius / 2 �� ����
	
	// ���� �ݿ��� �׸� ���� x ��ǥ�� 
	// Radius * 2 + Radius * 2 �̹Ƿ�, 
	// 2(Radius + Radius)
	// ��, (n �� �׸� ���� ������ ������ ��)
	// next GotoX = n * (Radius + Radius) 
	
	// ������ ������ ���� �׸��� ������ Radius * 2 + 1 �� �ݺ�
	// �ٸ�, y ���� ��� ������ ���߱� ���� 1 �� �ƴ϶� 2 ��ŭ �������ױ� ������
	// Radius �� �ݺ��ص� ���� X 
	
	// ��� ��ǥ ������ ������ �迭 ������ 
	int XPos_Sets[10000] = {0,};
	int YPos_Sets[10000] = {0,};
	// �迭 ������ �ε��� �� 
	int index = 0;
	
	// ���� ���� ���� 
	int CircleCnt = 0;
	// ��� ��ġ ������ 
	int GotoX, GotoY = 0;
	
	int k;
	// ���� �׸��� ������ Ȱ���� ��� �׸� ��� ��ǥ���� ��� �κ� 
	for (k = 0; k < 3; k++)
	{
		GotoX = CircleCnt * (Radius + Radius);
		GotoY = 0;
		Ypos = Radius;
		
		// ���� ������ � �׸��� �κ� 
		for (i = 0; i <= Radius / 2; i++) 
		{
			Xpos = -Radius;
			GotoX = CircleCnt * (Radius + Radius); 
			for (j = 0; j <= Radius * 2; j++)
			{
				// Console Ư���� ������ �����ϴ� ������
				// 2x : y �̹Ƿ� ������ ���߱� ���� y �� �߰� �̵� 
				
				if (sqrt(pow(Xpos, 2) + pow(Ypos, 2)) >= Radius - Thickness && sqrt(pow(Xpos, 2) + pow(Ypos, 2)) <= Radius + Thickness)
				{
					XPos_Sets[index] = GotoX + 4;
					YPos_Sets[index] = GotoY;
					
					index += 1;
				}		
	
				Xpos += 1;	
				GotoX += 1;
			}	
			// y �� �߰� �̵� 
			Ypos -= 2;
			GotoY += 1;
		}
		
		CircleCnt += 1;
		GotoX = CircleCnt * (Radius + Radius);
		GotoY = Radius / 2;
		Ypos = 0;
		
		// �Ʒ��� ������ � �׸��� �κ� 
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
			// y �� �߰� �̵� 
			Ypos -= 2;
			GotoY += 1;
		}
		
		// ���� ���� �߰� 
		CircleCnt += 1;
	}
	
	// �ӽ� ���� ����
	int temp = 0;
	// ����� ������ �ľ��ϴ� �κ� 
	int Count = 0;
	for (i = 0; XPos_Sets[i] != 0; i++)
		Count += 1; 
		
	// ��� �׸��� ��ǥ�� �� ũ�� �񱳸� ���� ��� �������� �׸��� ������ ����
	// - ���� ���� -
	// 1) x �� ���� ������� (��, x �� ���� ��������) 

	// x �� y �� ���� �����ϴ� �κ� (x �� y ��ǥ�� ���ϸ� �ȵǴ� �������̹Ƿ�) 
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
	
	// ���� ��� ����ϴ� �κ� 
	for (i = 0; i < Count; i++)
	{
		Gotoxy(XPos_Sets[i], YPos_Sets[i] + Radius);
		Sleep(30); 
		printf("*");
	} 

	// �Լ� ��� �׸� �� ��� �� �� �ڵ� 
	
	// ���� (0, 0)�� �������� �׸��� ���� ������
	// x^2 + y^2 = r^2
	// ��(x^2 + y^2) = r
	
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
	// Ŀ�� ���� 
	Cursor.dwSize = 1;
	// Ŀ�� ���� ���� 
	Cursor.bVisible = FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Cursor);
}
