/*  Author:HuangXu 
	E-mail:maoliloveyou@foxmail.com
	Date: 2021-11-30                 */

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <string.h>

#define Game_Success 2048
#define Game_Start 1

int board[4][4];
int game_statu; // ��Ϸ״̬��2��ʾ��Ϸ�ɹ� 1��ʾ��Ϸʧ�ܣ�0��ʾ����
int score;
int record;
int game_exit;
//��Ϸ���󲿷�
int count_board()
{ //���һ��ж��ٸ���λ
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
	int index = rand() % availableSquares; // ��һ����λ������
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
						board[row][column] = 1024;
					}
					else
					{
						board[row][column] = 512;
					}
					return;
				}else index--;
			}
		}
	}
}
void rotate_board()
{
	int i,j, tmp;
	for (i=0;i < 2;i++)
	{
		for (j=i;j < 3-i;j++)
		{
			tmp =board[i][j];
			board[i][j]=board[j][3-i];
			board[j][3- i]=board[3- i][3- j];
			board[3 - i][3 - j]=board[3 - j][i];
			board[3 - j][i]=tmp;
		}
	}
}
void move_left() //���ƶ� �ƶ���ǵüӷ����Լ�ˢ�½��棡
{
	int row, column, target;
	for (row = 0; row < 4; row++)
	{
		for (column = 1, target = 0; column < 4; column++)
		{
			if (board[row][column] > 0)
			{
				if (board[row][target] == board[row][column])
				{ //�ϲ�����
					score += board[row][target++] *= 2;
					board[row][column] = 0;
				}
				else if (board[row][target] == 0)
				{ //�ƶ�����
					board[row][target] = board[row][column];
					board[row][column] = 0;
				}
				else
				{
					board[row][++target] = board[row][column];
					if (column != target)
					{
						/* �ж�j���k���Ƿ�ԭ�ȾͰ���һ�����������j�ֵΪ�գ�ֵΪ0�� */
						board[row][column] = 0;
					}
				}
			}
		}
	}
}
void move_right()
{
	rotate_board();
	rotate_board();
	move_left();
	rotate_board();
	rotate_board();
}
void move_down()
{
	rotate_board();
	rotate_board();
	rotate_board();
	move_left();
	rotate_board();
}
void move_up()
{
	rotate_board();
	move_left();
	rotate_board();
	rotate_board();
	rotate_board();
}

//�û����󲿷�
//void update_record()
//{
//	record = score;
//	FILE *fp = fopen(config_path, "w");
//	if (fp)
//	{
//		fwrite(&record, sizeof(record), 1, fp);
//		fclose(fp);
//	}
//}
void clear_screen()
{
	// ���ع�겢����������
	COORD pos = {0, 0};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
	CONSOLE_CURSOR_INFO info = {1, 0};
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
}
void game_judge()
{
	int row, column, cnt = 0;
	for (row = 0; row < 4; row++)
	{
		for (column = 0; column < 4; column++)
		{
			if (board[row][column] == Game_Success)
				game_statu = 2; //��Ϸʤ��
			return;
		}
	}
	for (row = 0; row < 4; row++)
	{
		for (column = 0; column < 4; column++)
		{
			if (board[row][column] == board[row][column + 1] || board[column][row] == board[column + 1][row])
				game_statu = 0; //��Ϸ��δ����
			return;
		}
	}
	game_statu = 1; //��Ϸʧ��
	return;
}
void show_game_surface()
{
	clear_screen();
	printf("\n\n");
	printf("                                         2048\n");
	printf("                            ��ǰ�÷�: %05d     ���ս��: %05d\n", score, record);
	printf("               **************************************************");
	printf("\n\n                             �����������Щ��������Щ��������Щ���������\n");
	int row, column;
	for (row = 0; row < 4; row++)
	{
		printf("                             ��");
		for (column = 0; column < 4; column++)
		{
			if (board[row][column] != 0)
			{ //��������ּ��
				if (board[row][column] < 10)
				{
					printf("  %d ��", board[row][column]);
				}
				else if (board[row][column] < 100)
				{
					printf(" %d ��", board[row][column]);
				}
				else if (board[row][column] < 1000)
				{
					printf(" %d��", board[row][column]);
				}
				else
				{
					printf("%4d��", board[row][column]);
				}
			}
			else
				printf("    ��");
		}
		if (row < 3)
		{
			printf("\n                             �����������੤�������੤�������੤��������\n");
		}
		else
		{
			printf("\n                             �����������ة��������ة��������ة���������\n");
		}
	}
	printf("\n");
	printf("               **************************************************\n");
	printf("                 ������[��][��][��][��] �ƶ�����, [R]���� [ESC] �˳�");
	game_judge();
	if (game_statu == 2)
	{
		printf("\n                    Congratulations! ��Ҫ����һ����? [Y/N]:     ");
	}
	if (game_statu == 1)
	{
		printf("\n                      GAME OVER! ��Ҫ����һ����? [Y/N]:     ");
	}
	if (game_exit)
	{
		printf("\n                               ȷ���˳���? [Y/N]:");
	}
	if (score > record)
	{
//		update_record();
	}
	// fflush(0);
}
int restart_game()
{
	memset(board, 0, 16);
	score = 0;
	game_statu = 0;
	game_exit = 0;
	add_random();
	add_random();
	show_game_surface();
}
void release_game()
{
	system("cls");
	CONSOLE_CURSOR_INFO info = {1, 1};
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
	exit(0);
}
int game_process() //���ּ��̴��ڻ�ȡ��λ״̬��ʵʱ����
{
	while (Game_Start)
	{
		int command = getch();
		if (game_exit)
		{
			if (command == 'y' || command == 'Y')
			{
				clear_screen();
				release_game();
				exit(0);
			}
			else if (command == 'n' || command == 'N')
			{
				game_exit = 0;
				show_game_surface();
				continue;
			}
			continue;
		}
		if (game_statu)
		{
			if (command == 'y' || command == 'Y')
			{
				restart_game();
				continue;
			}
			else if (command == 'n' || command == 'N')
			{
				release_game();
				exit(0);
			}
			continue;
		}
		if (command == 75)
			move_left();
		if (command == 80)
			move_down();
		if (command == 72)
			move_up();
		if (command == 77)
			move_right();
		if(command==75||command==80||command==72||command==77){
			add_random();
			show_game_surface();
		}
		if (command == 27)
		{
			game_exit = 1;
			show_game_surface();
		}
		if (command == 'r' || command == 'R')
			restart_game();
	}
}

void load_game()
{
	restart_game(); 
	show_game_surface();
}

int main(void)
{
	load_game();
	game_process();
	return 0;
}

/*
reference:
[1]���Ӻϲ��뷭ת���̵�ʵ�֡�����ָ���Ŀμ�
[2]C����ʹ��getch()��ȡ�����
https://blog.csdn.net/u013521296/article/details/77103697
[3]���ع�꺯��
https://blog.csdn.net/qq_17155501/article/details/82939244
[4]���̽�������Ƽ�˼·��չ��C����ʵ��2048��Ϸ
https://blog.csdn.net/qq_44275213/article/details/110052926
*/

