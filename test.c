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
	int count = 0, rnd, gamecnt;  //변수 추가부분 
	int r_count = 0;
	char *target = "▣";
	srand((unsigned)time(NULL));   //시변 랜덤 함수의 사용 
	intro_game();
	printf("게임 횟수를 입력: ");    //추가부분 
	scanf_s("%d", &gamecnt);       //추가부분 

	do
	{
		system("cls");  //화면 지우고 
		draw_rectangle(20, 20); //게임 화면 테두리 출력 20*20 
		rnd = rand() % 35 + 4;//타겟의 랜덤 위치를 4~35 사이로 지정 
		gotoxy(rnd, 2); //타겟 위치 선정 
		printf("%s", target); //타겟 위치 출력 
		count++; //게임이 진행 됬으므로 카운트는 증가 
		display_text(count, r_count); //게임 정보 출력 
		r_count = game_control(r_count, rnd); //실제 게임 진행 및 맞춘 횟수를 r_count 에 저장 
	} while (count < gamecnt);    //수정 부분 

	system("cls");                 //추가 부분 
	printf(" %d 회 맞췄습니다.\n", r_count);   //추가 부분     //게임 종료후 결과 출력 부분 

	return 0;
}

void intro_game(void){
	int gamecnt;
	printf("고정된 물체 맞추기\n\n");
	printf("고정된 물체를 이동하면서 \n");
	printf("목표물(■)을 맞추는 게임입니다. \n");
	printf("화살은 스페이스키로 발사합니다. \n\n");
	printf("아무키나 누르면 시작합니다.\n");
	_getch();
}

void horizontal_slide(int x, int y, char *c2){
	gotoxy(x, y);     //말의 위치 선정 
	printf("%s", c2); //말 출력 
	Sleep(50);         //말의 움직임은 지연속도 50을 가지고 움직임 
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
	gotoxy(46, 2); //커서위치 이동 
	printf("스페이스키를 누르면\n"); //이동된 커서위치에서 출력 
	gotoxy(46, 3);
	printf("화살이 발사됩니다.\n");
	gotoxy(46, 5);
	printf("횟수 : %d", count);
	gotoxy(46, 6);
	printf("성공 : %d", r_count);
}

int game_control(int r_c, int rnd)
{
	int i = 1, k = 1, y;
	char *horse = "▲", chr;
	do
	{
		i += k;
		if (i > 39) //x범위 //말의 움직임을 관장하는 반복문 
			k = -1;
		else if (i < 3) //y출력위치 
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
			printf("↑"); // 화살표시 
			Sleep(20);    // 지연시간 
			printf("\b ");
		}
		if ((rnd <= i + 1) && (i <= (rnd - 1)))
		{
			gotoxy(rnd, 2);
			printf("☆"); // 30page 연습문제 5번 참고 
			gotoxy(46, 8);
			printf("맞았습니다. ");
			Sleep(50);  // 시간지연 
			return r_c += 1;
		}
		else
			return r_c;
		gotoxy(1, 24);
		printf("아무키나 누르면 다음 진행...");
		_getch();
	}
}

void gotoxy(int x, int y)  //커서위치 지정 함수 
{
	COORD Pos = { x - 1, y - 1 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}