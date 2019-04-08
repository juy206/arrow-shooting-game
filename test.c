#include <stdio.h> 
#include <conio.h> 
#include <stdlib.h> 
#include <time.h> 
#include <windows.h> 
#define _CRT_SECURE_NO_WARNINGS

void intro_game(void);
void horizontal_slide(int x, int y, char *c2);
void draw_rectangle(int r, int c);
void display_text(int count, int r_count);
int game_control(int r_c, int rnd);
void gotoxy(int x, int y);

int main(void){
	int count = 0, rnd, gamecnt;  //���� �߰��κ� 
	int r_count = 0;
	char *target = "��";
	srand((unsigned)time(NULL));   //�ú� ���� �Լ��� ��� 
	intro_game();
	printf("���� Ƚ���� �Է�: ");    //�߰��κ� 
	scanf_s("%d", &gamecnt);       //�߰��κ� 

	do
	{
		system("cls");  //ȭ�� ����� 
		draw_rectangle(20, 20); //���� ȭ�� �׵θ� ��� 20*20 
		rnd = rand() % 35 + 4;//Ÿ���� ���� ��ġ�� 4~35 ���̷� ���� 
		gotoxy(rnd, 2); //Ÿ�� ��ġ ���� 
		printf("%s", target); //Ÿ�� ��ġ ��� 
		count++; //������ ���� �����Ƿ� ī��Ʈ�� ���� 
		display_text(count, r_count); //���� ���� ��� 
		r_count = game_control(r_count, rnd); //���� ���� ���� �� ���� Ƚ���� r_count �� ���� 
	} while (count < gamecnt);    //���� �κ� 

	system("cls");                 //�߰� �κ� 
	printf(" %d ȸ ������ϴ�.\n", r_count);   //�߰� �κ�     //���� ������ ��� ��� �κ� 

	return 0;
}

void intro_game(void){
	int gamecnt;
	printf("������ ��ü ���߱�\n\n");
	printf("������ ��ü�� �̵��ϸ鼭 \n");
	printf("��ǥ��(��)�� ���ߴ� �����Դϴ�. \n");
	printf("ȭ���� �����̽�Ű�� �߻��մϴ�. \n\n");
	printf("�ƹ�Ű�� ������ �����մϴ�.\n");
	_getch();
}

void horizontal_slide(int x, int y, char *c2){
	gotoxy(x, y);     //���� ��ġ ���� 
	printf("%s", c2); //�� ��� 
	Sleep(50);         //���� �������� �����ӵ� 50�� ������ ������ 
	printf("\b ");
}

void draw_rectangle(int c, int r) {
	int i, j;
	unsigned char a = 0xa6;
	unsigned char b[7];
	for (i = 0; i < 7; i++)
		b[i] = 0xa0 + i;
	printf("%c%c", a, b[3]);
	for (i = 0; i < c; i++)
		printf("%c%c", a, b[1]);
	printf("%c%c", a, b[4]);
	printf("\n");
	for (i = 0; i < r; i++)
	{
		printf("%c%c", a, b[2]);
		for (j = 0; j < c * 2; j++)
			printf(" ");
		printf("%c%c", a, b[2]);
		printf("\n");
	}
	printf("%c%c", a, b[6]);
	for (i = 0; i < c; i++)
		printf("%c%c", a, b[1]);
	printf("%c%c", a, b[5]);
	printf("\n");
}

void display_text(int count, int r_count){
	gotoxy(46, 2); //Ŀ����ġ �̵� 
	printf("�����̽�Ű�� ������\n"); //�̵��� Ŀ����ġ���� ��� 
	gotoxy(46, 3);
	printf("ȭ���� �߻�˴ϴ�.\n");
	gotoxy(46, 5);
	printf("Ƚ�� : %d", count);
	gotoxy(46, 6);
	printf("���� : %d", r_count);
}

int game_control(int r_c, int rnd)
{
	int i = 1, k = 1, y;
	char *horse = "��", chr;
	do
	{
		i += k;
		if (i > 39) //x���� //���� �������� �����ϴ� �ݺ��� 
			k = -1;
		else if (i < 3) //y�����ġ 
			k = +1;
		horizontal_slide(i + 1, 21, horse);
		horizontal_slide(i, 21, " ");
	} while (!_kbhit());
	chr = _getch();
	y = 21;
	if (chr == 32)
	{
		while (y > 2)
		{
			y -= 1;
			gotoxy(i + 1, y);
			printf("��"); // ȭ��ǥ�� 
			Sleep(20);    // �����ð� 
			printf("\b ");
		}
		if ((rnd <= i + 1) && (i <= (rnd - 1)))
		{
			gotoxy(rnd, 2);
			printf("��"); // 30page �������� 5�� ���� 
			gotoxy(46, 8);
			printf("�¾ҽ��ϴ�. ");
			Sleep(50);  // �ð����� 
			return r_c += 1;
		}
		else
			return r_c;
		gotoxy(1, 24);
		printf("�ƹ�Ű�� ������ ���� ����...");
		_getch();
	}
}

void gotoxy(int x, int y)  //Ŀ����ġ ���� �Լ� 
{
	COORD Pos = { x - 1, y - 1 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}