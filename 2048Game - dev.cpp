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

FILE *mem;
int board[4][4];
int history_board[11][4][4];
int history_status;
int back_board_cmd_remain;
int game_statu; // ��Ϸ״̬��2��ʾ��Ϸ�ɹ� 1��ʾ��Ϸʧ�ܣ�0��ʾ����
int failed_back; 
int score;
int record;
int game_exit;
//������ʾ��û�㶨

//��Ϸ���󲿷�
int count_board()
{
	//���һ��ж��ٸ���λ
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
						board[row][column] = 4;
					}
					else
					{
						board[row][column] = 2;
					}
					return;
				}
				else
					index--;
			}
		}
	}
}
void rotate_board()
{
	int i, j, tmp;
	for (i = 0; i < 2; i++)
	{
		for (j = i; j < 3 - i; j++)
		{
			tmp = board[i][j];
			board[i][j] = board[j][3 - i];
			board[j][3 - i] = board[3 - i][3 - j];
			board[3 - i][3 - j] = board[3 - j][i];
			board[3 - j][i] = tmp;
		}
	}
}
void move_left()
{
	//���ƶ� �ƶ���ǵüӷ����Լ�ˢ�½��棡
	int row, column, target;
	for (row = 0; row < 4; row++)
	{
		for (column = 1, target = 0; column < 4; column++)
		{
			if (board[row][column] > 0)
			{
				if (board[row][target] == board[row][column])
				{
					//�ϲ�����
					score += board[row][target++] *= 2;
					board[row][column] = 0;
				}
				else if (board[row][target] == 0)
				{
					//�ƶ�����
					board[row][target] = board[row][column];
					board[row][column] = 0;
				}
				else
				{
					board[row][++target] = board[row][column];
					if (column != target)
					{
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
void save(void)
{
	if ((mem = fopen("memory.txt", "w")) == NULL)
	{
		return;
	}
	fprintf(mem, "%d ", record);
	int row, column;
	for (row = 0; row < 4; row++)
	{
		for (column = 0; column < 4; column++)
		{
			fprintf(mem, "%d ", board[row][column]);
		}
	}
	fclose(mem);
}
void load(void)
{
	if ((mem = fopen("memory.txt", "r")) == NULL)
	{
		return;
	}
	fscanf(mem, "%d", &record);
	int row, column;
	for (row = 0; row < 4; row++)
	{
		for (column = 0; column < 4; column++)
		{
			int i;
			fscanf(mem, "%d", &i);
			board[row][column] = i;
		}
	}
	fclose(mem);
}
void save_backboard()
{
	int row, column, flag = 0;
	if (back_board_cmd_remain)
	{
		for (row = 0; row < 4; row++)
		{
			for (column = 0; column < 4; column++)
			{
				if (board[row][column] != history_board[history_status][row][column])
				{
					flag = 1;
					break;
				}
			}
		}
		if (flag)
		{
			if (back_board_cmd_remain < 10)
				back_board_cmd_remain++;
			history_status++;
			if (history_status == 11)
				history_status = 1;
			for (row = 0; row < 4; row++)
			{
				for (column = 0; column < 4; column++)
				{
					history_board[history_status][row][column] = board[row][column];
				}
			}
		}
	}
	else
	{
		if (back_board_cmd_remain < 11)
			back_board_cmd_remain++;
		history_status++;
		if (history_status == 11)
			history_status = 1;
		for (row = 0; row < 4; row++)
		{
			for (column = 0; column < 4; column++)
			{
				history_board[history_status][row][column] = board[row][column];
			}
		}
	}
}
int back_board()
{
	if (!back_board_cmd_remain)
		return 0;
	back_board_cmd_remain--;
	int row, column;
	for (row = 0; row < 4; row++)
	{
		for (column = 0; column < 4; column++)
		{
			board[row][column] = history_board[history_status][row][column];
		}
	}
	history_status--;
	if (history_status == 0)
		history_status = 10;
	return 1;
}
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
	int row, column;
	for (row = 0; row < 4; row++)
	{
		for (column = 0; column < 4; column++)
		{
			if (board[row][column] == Game_Success)
			{
				game_statu = 2; //��Ϸʤ��
				return;
			}
		}
	}
	if (count_board())
	{
		game_statu = 0;
		return;
	}
	for (row = 0; row < 3; row++)
	{
		for (column = 0; column < 3; column++)
		{
			if (board[row][column] == board[row][column + 1] || board[row][column] == board[row + 1][column])
			{
				game_statu = 0; //��Ϸ��δ����
				return;
			}
		}
	}
	for (column = 0; column < 3; column++)
	{
		if (board[3][column] == board[3][column + 1])
		{
			game_statu = 0; //��Ϸ��δ����
			return;
		}
	}
	for (row = 0; row < 3; row++)
	{
		if (board[row][3] == board[row + 1][3])
		{
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
	if (score > record)
	{
		record = score;
		save();
	}
	printf("\n\n");
	printf("                                       2048\n\n");
	printf("                        ��ǰ�÷�: %05d     ���ս��: %05d\n", score, record);
	printf("               **************************************************");
	printf("\n\n                             �����������Щ��������Щ��������Щ���������\n");
	int row, column;
	for (row = 0; row < 4; row++)
	{
		printf("                             ��");
		for (column = 0; column < 4; column++)
		{
			if (board[row][column] != 0)
			{
				//��������ּ��
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
	printf("               ������[��][��][��][��]�ƶ�����  [R]���� [ESC] �˳�\n");
	printf("                     [B]����     ��ǰ�ɻ��������%d  ", back_board_cmd_remain);
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
	if (failed_back){
		printf("\n\n                           Sorry! ��û�л���Ļ���!");
		failed_back=0;
	}
	printf("\n                                                                ");
	printf("\n                                                                ");
}
void restart_game()
{
	memset(board, 0, sizeof(board));
	memset(history_board,0,sizeof(history_board));
	score = 0;
	game_statu = 0;
	game_exit = 0;
	back_board_cmd_remain = 0;
	failed_back=0;
	history_status = 10;
	add_random();
	add_random();
	show_game_surface();
}
int game_process()
{
	//���ּ��̴��ڻ�ȡ��λ״̬��ʵʱ����
	while (Game_Start)
	{
		int command = _getch();
		if (game_exit)
		{
			if (command == 'y' || command == 'Y')
			{
				system("cls");
				printf("\n\n");
				printf("                                       2048 (���潫��3s��ر�)\n\n");
				printf("                        ��ǰ�÷�: %05d     ���ս��: %05d\n", score, record);
				printf("               **************************************************");
				printf("\n\n\n\n                                      �ټ���     \n\n\n");
				printf("\n\n                   *������Ϸ�����Ѿ����棬�´δ򿪽����Զ���ȡ     \n\n\n");
				printf("               **************************************************\n\n");
				save();
				Sleep(3 * 1000);
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
				//				release_game();
				system("cls");
				printf("\n\n");
				printf("                                       2048 (���潫��3s��ر�)\n\n");
				printf("                        ��ǰ�÷�: %05d     ���ս��: %05d\n", score, record);
				printf("               **************************************************");
				printf("\n\n\n\n                                      �ټ���     \n\n\n");
				printf("\n\n                   *������Ϸ�����Ѿ����棬�´δ򿪽����Զ���ȡ     \n\n");
				printf("               **************************************************");
				Sleep(3 * 1000);
				exit(0);
			}
			continue;
		}
		if (command == 75 || command == 80 || command == 72 || command == 77)
		{
			save_backboard();
		}
		if (command == 75)
			move_left();
		if (command == 80)
			move_down();
		if (command == 72)
			move_up();
		if (command == 77)
			move_right();
		if (command == 75 || command == 80 || command == 72 || command == 77)
		{
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
		if (command == 'b' || command == 'B'){
			if(!back_board()){
				failed_back=1;
			}
			show_game_surface();
		}
	}
}

int main(void)
{
	restart_game();
	load();
	show_game_surface();
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
[5]̰����ʵ�ִ浵����
https://blog.csdn.net/baidu_30000217/article/details/53220036
https://www.csdn.net/tags/MtjaQg0sOTIwMTMtYmxvZwO0O0OO0O0O.html
*/
