/*  Author:HuangXu 
	E-mail:maoliloveyou@foxmail.com
	Date: 2021-11-30                 */

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

int get_board_status(){

}
void add_random(){

}
void clear_screen() {
	// 隐藏光标并清理窗口文字
	COORD pos = {0, 0};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
	CONSOLE_CURSOR_INFO info = {1, 0};
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
}
int check_game_over(){

}
void draw_game_surface(){

}
int restart_game(){

}
void move_left(){

}
void move_right(){

}
void move_up(){

}
void move_down(){

}
int game_process(){//保持键盘处在获取键位状态并实时反馈
	
}
void load_game(){

}
void release_game(int signal) {
	system("cls");
	CONSOLE_CURSOR_INFO info = {1, 1};
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
	exit(0);
}
int main(){
	
} 

/*
reference:
[1]C语言使用getch()读取方向键
https://blog.csdn.net/u013521296/article/details/77103697
[2]隐藏光标函数
https://blog.csdn.net/qq_17155501/article/details/82939244

*/
