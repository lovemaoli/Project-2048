/*  Author:HuangXu 
	E-mail:maoliloveyou@foxmail.com
	Date: 2021-11-30                 */

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

#define Game_Success 16

int board[4][4];
int game_statu; // 游戏状态，2表示游戏成功 1表示游戏失败，0表示正常
int score;
int record;
int exit;

int count_board()
{ //查找还有多少个空位
	int row, column, cnt = 0;
	for (row = 0; row < 4; row++)
	{
		for (column = 0; column < 4; column++)
		{
			if (board[row][column] == 0)
				cnt++;
		}
	}
	return cnt;
}
void add_random()
{
	srand((unsigned)(time(NULL)));
	int availableSquares = count_board();
	if (!availableSquares)
		return;
	int index = rand() % availableSquares; // 找一个空位放数字
	int row, column;
	for (row = 0; row < 4; row++)
	{
		for (column = 0; column < 4; column++)
		{
			if (board[row][column] == 0)
			{
				if (index == 0)
				{
					if (rand() % 10 == 0)
					{
						board[row][column] = 4;
					}
					else
					{
						board[row][column] = 2;
					}
					return;
				}
			}
			else
			{
				index--;
			}
		}
	}
}
void clear_screen()
{
	// 隐藏光标并清理窗口文字
	COORD pos = {0, 0};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
	CONSOLE_CURSOR_INFO info = {1, 0};
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
}
int game_judge()
{
	int row, column, cnt = 0;
	for (row = 0; row < 4; row++)
	{
		for (column = 0; column < 4; column++)
		{
			if (board[row][column] == Game_Success)
				game_statu = 2; //游戏胜利
			return;
		}
	}
	for (row = 0; row < 4; row++)
	{
		for (column = 0; column < 4; column++)
		{
			if (board[row][column] == board[row][column + 1] || board[column][row] == board[column + 1][row])
				game_statu = 0; //游戏尚未结束
			return;
		}
	}
	game_statu = 1; //游戏失败
	return;
}
void show_game_surface()
{
	clear_screen();

	printf("\n\n");
	printf("                                    2048\n");
	printf("                            当前得分: %05d     最佳战绩: %06d\n", score, record);
	printf("               **************************************************");
	printf("\n\n                             ┌────┬────┬────┬────┐\n");
	int row, column;
	for (row = 0; row < 4; row++)
	{
		printf("                             │");
		for (column = 0; column < 4; column++)
		{
			if (board[row][column] != 0)
			{
				if (board[row][column] < 10)
				{
					printf("  %d │", board[row][column]);
				}
				else if (board[row][column] < 100)
				{
					printf(" %d │", board[row][column]);
				}
				else if (board[row][column] < 1000)
				{
					printf(" %d│", board[row][column]);
				}
				else
				{
					printf("%4d│", board[row][column]);
				}
			}
			else
				printf("    │");
		}
		if (row < 3)
		{
			printf("\n                             ├────┼────┼────┼────┤\n");
		}
		else
		{
			printf("\n                             └────┴────┴────┴────┘\n");
		}
	}
	printf("\n");
	printf("               **************************************************\n");
	printf("                 按键：[↑][↓][←][→] 移动数字, [R]重置 [ESC] 退出");
	game_judge();
	if (game_statu == 2)
	{
		printf("\n                    Congratulations! 想要再玩一遍吗? [Y/N]:     ");
	}
	if (game_statu == 1)
	{
		printf("\n                      GAME OVER! 想要再玩一遍吗? [Y/N]:     ");
	}
	if (exit)
	{
		printf("\n                               确定退出吗? [Y/N]:");
	}

	fflush(0);
}
int restart_game()
{
	score = 0;
	game_statu = 0;
	exit = 0;
	add_random();
	add_random();
	show_game_surface();
}
//先移动 移动后记得加方块以及刷新界面！
void move_left()
{
	int row, column, target;
	for (row = 0; row < 4; row++)
	{
		for (column = 1, target = 0; column < 4; column++)
		{
			if (board[row][column] > 0)
			{
				if (board[row][target] == board[row][column])
				{ //合并方块
					score += board[row][target++] *= 2;
					board[row][column] = 0;
				}
				else if (board[row][target] == 0)
				{ //移动方块
					board[row][target] = board[row][column];
					board[row][column] = 0;
				}
				else
				{
					board[row][++target] = board[row][column];
					if (column != target)
					{
						/* 判断j项和k项是否原先就挨在一起，若不是则把j项赋值为空（值为0） */
						board[row][column] = 0;
					}
				}
			}
		}
	}
}
void rotate_board()
{
	int i, j, n = SIZE;
	int tmp;
	for (i = 0; i < n / 2; i++)
	{
		for (j = i; j < n ‐ i ‐ 1; j++)
		{
			tmp = board[i][j];
			board[i][j] = board[j][n ‐ i ‐ 1];
			board[j][n ‐ i ‐ 1] = board[n ‐ i ‐ 1][n ‐ j ‐ 1];
			board[n ‐ i ‐ 1][n ‐ j ‐ 1] = board[n ‐ j ‐ 1][i];
			board[n ‐ j ‐ 1][i] = tmp;
		}
	}
}
void move_right()
{
}
void move_up()
{
}
void move_down()
{
}
int game_process()
{ //保持键盘处在获取键位状态并实时反馈
}
void load_game()
{
}
void release_game(int signal)
{
	system("cls");
	CONSOLE_CURSOR_INFO info = {1, 1};
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
	exit(0);
}
int main()
{
}

/*
reference:
[1]C语言使用getch()读取方向键
https://blog.csdn.net/u013521296/article/details/77103697
[2]隐藏光标函数
https://blog.csdn.net/qq_17155501/article/details/82939244
[3]C语言实现2048游戏（Windows版）(借鉴了棋盘的格式)
https://blog.csdn.net/qq_44275213/article/details/110052926
*/
