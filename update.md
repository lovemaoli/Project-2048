###bug 以及 修复
1.达到上限值不提示游戏成功
解决：	game_statu = 2;return;没加括号 直接return导致判断错误
2.重新开始游戏棋盘不成功清零
解决：①memset(board, 0, 16);→memset(board, 0, sizeof(board));
	本以为是没加system("cls");的问题 经过测试后发现不需要加此命令
3.按esc后取消退出仍然提示
解决：需要清屏
	更佳方法：使用末尾输出两行空行叠加修改
4.存档读入失败
解决：应该先初始化 后读入存档
5.最佳战绩和当前分数不匹配
解决：将更新分数存在show_game_surface()中而不是game_process()中
6.判断失败错误
count_board没加括号