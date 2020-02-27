// Maze.h : 初始化头文件

// Start
#pragma once			// 防止该头文件被多次调用

// Head
#include <time.h>		// 时间作为随机生成种子
#include <conio.h>		// 获取键盘信息用
#include <vector>		// 使用 STL vector
#include <algorithm>	// 使用 random_shuffle 函数
#include <graphics.h>	// 引用图形库头文件

// Block
enum BLOCK {WALL = 1, END, YOU, ROAD};	// 墙，终点，起点，路

// Box
#define MY_OK 0							// 只有“确定”按钮
#define MY_YESNO 1						// 有“是”按钮和“否”按钮

//Other
#define INF 2147483647					// 无限大， Prim 随机生成迷宫用