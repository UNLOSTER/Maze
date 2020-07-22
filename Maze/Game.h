// Game.h : 游戏类头文件

#pragma once		// 防止该头文件被多次调用

#include "Maze.h"	// 初始化头文件

// 游戏类

// 刷新界面、放置按钮、输出对话框类
class COther
{
public:
	COther() {}
	~COther() {}
	
	void putAll();																											// 绘制背景
	bool button(int a, int b, wchar_t str[]);																				// 放置按钮
	int putMessageBox(int x, int y, int wight, int hight, wchar_t title[], wchar_t * text[], int g_num, int var = MY_OK);	// 输出对话框
};

// 冒险模式类
class CAdventrue
{
public:
	int pass, all_pass;												// 关卡和总关卡
	int to_x, to_y, x, y, room[150][150], n, m;						// 终点坐标、任务坐标、迷宫地图储存和迷宫大小
	int tot, reg[2600][2600], feg[2600][2600], flag[3][2600];	// 图节点总数、邻接矩阵、辅助邻接矩阵和迷宫中坐标与图节点编号关系记录
	bool fmap[150][150], tip[2600];								// 辅助迷宫地图、图节点是否走过记录
	
	CAdventrue() {}
	~CAdventrue() {}
	
	virtual void game();									// 各模式（系列）核心

	bool winPut();											// 通过一关卡界面
	void gameOver();										// 通过全关卡界面
	void man_Move();										// 人物移动处理
	void clear();											// 清空数据处理

	int search(int x, int y);								// DFS 搜索生成迷宫核心
	int dfs(int step);										// 图论 DFS 搜索生成迷宫核心
	int my_line(int x_1, int y_1, int x_2, int y_2);		// 辅助函数
};

// 冒险模式-森林系列类
class CForest : public CAdventrue
{
public:
	CForest() {}
	~CForest() {}
	
	void game();	// 各模式（系列）核心

private:
	void prim();	// Prim 随机生成迷宫
	void putRoom();	// 绘制界面
};

// 冒险模式-地牢系列类
class CDungeon : public CAdventrue
{
public:
	CDungeon() {}
	~CDungeon() {}
	
	void game();	// 各模式（系列）核心

private:
	void deepFS();	// 图论 DFS 随机生成迷宫
	void putRoom(); // 绘制界面
};

// 冒险模式-地狱系列类
class CInfernal : public CAdventrue
{
public:
	CInfernal() {}
	~CInfernal() {}
	
	void game();	// 各模式（系列）核心

private:
	void myKLS();	// 暴力 DFS 随机生成迷宫
	void putRoom(); // 绘制界面
};

// 帮助信息类
class CHelp
{
public:
	CHelp() {}
	~CHelp() {}
	
	void put();		// 绘制界面
};
