// Maze.cpp : 程序开端文件

#include "Game.h"						// 游戏头文件

// 程序主函数
int main()
{
	srand((unsigned int)time(NULL));	// 随机种子

	initgraph(640, 480);				// 创建图形化窗口

	CAdventrue* bed = new CAdventrue();
	bed->game();						// 开始游戏

	delete bed;
	bed = NULL;

	closegraph();
	return 0;							// 游戏结束
}