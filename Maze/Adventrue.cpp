// Adventrue.cpp : 冒险模式类文件

#include "Game.h"	// 游戏头文件

// 全局变量

char ch;						// 键盘消息
long long times, start_time;	// 计时器
MOUSEMSG m_msg;				// 鼠标消息

// CAdventure 类函数实现

// 冒险模式核心
void CAdventrue::game()
{
	CAdventrue* Adv;
	CHelp* help = new CHelp();
	COther* but = new COther();

	setbkmode(TRANSPARENT);

	BeginBatchDraw();

	while (1)
	{
		if (_kbhit())		// 键盘消息获取
		{
			ch = _getch();	// 键盘消息获取
			if (ch == 27)	// 按 Esc 退出
			{
				break;
			}
		}

		while (MouseHit())	// 鼠标消息获取
			m_msg = GetMouseMsg();

		but->putAll();		// 绘制背景

		for (int i = 0; i <= 3; i++)
		{
			settextcolor(RGB(100, 100, 100));
			settextstyle(70, 0, L"微软雅黑");
			outtextxy(235 + i, 85 + i, L"迷　宫");
		}
		settextcolor(WHITE);
		settextstyle(70, 0, L"微软雅黑");
		outtextxy(235 + 3, 85 + 3, L"迷　宫");		// 标题输出

		if (but->button(280, 200, L"　森林　"))		// 森林系列按钮
		{
			Adv = new CForest();
			Adv->all_pass = rand() % 50 + 25;
			Adv->pass = 1;
			Adv->n = 15;
			Adv->m = 15;
			times = 0;
			Adv->game();
			delete Adv;
			Adv = NULL;
		}

		if (but->button(280, 260, L"　地牢　"))		// 地牢系列按钮
		{
			Adv = new CDungeon();
			Adv->all_pass = rand() % 50 + 25;
			Adv->pass = 1;
			Adv->n = 25;
			Adv->m = 25;
			times = 0;
			Adv->game();
			delete Adv;
			Adv = NULL;
		}

		if (but->button(280, 320, L"　地狱　"))		// 地狱系列按钮
		{
			Adv = new CInfernal();
			Adv->all_pass = rand() % 50 + 25;
			Adv->pass = 1;
			Adv->n = 45;
			Adv->m = 45;
			times = 0;
			Adv->game();
			delete Adv;
			Adv = NULL;
		}

		if (but->button(280, 380, L"　帮助　"))		// 帮助信息按钮
			help->put();

		LOGFONT f;
		gettextstyle(&f);
		f.lfWidth = 10;
		wcscpy_s(f.lfFaceName, L"微软雅黑 Light");
		f.lfQuality = ANTIALIASED_QUALITY;
		settextstyle(&f);
		settextcolor(WHITE);

		outtextxy(340, 153, L"V1.0 By Lost");
		outtextxy(249, 440, L"按 Esc 退出游戏");	// 输出其他

		FlushBatchDraw();
		Sleep(5);
	}

	EndBatchDraw();

	delete but;
	but = NULL;
	delete Adv;
	Adv = NULL;
}

// 通过一关卡界面
bool CAdventrue::winPut()
{
	COther* but = new COther();

	wchar_t title[50];

	swprintf_s(title, L"使用时间 %lld s\0", times);

	while (1)
	{
		if (_kbhit())				// 键盘消息获取
			ch = _getch();

		while (MouseHit())
			m_msg = GetMouseMsg();	// 鼠标消息获取

		but->putAll();				// 绘制背景

		for (int i = 0; i <= 3; i++)
		{
			settextcolor(RGB(100, 100, 100));
			settextstyle(52, 0, L"黑体");
			outtextxy(140 + i, 90 + i, title);
		}
		settextcolor(WHITE);
		settextstyle(52, 0, L"黑体");
		outtextxy(140 + 3, 90 + 3, title);		// 标题输出

		if (but->button(273, 215, L" 下一关"))	// 下一关按钮
			break;

		if (but->button(273, 300, L"回到主页"))	// 回到主页按钮
		{
			wchar_t* text[10];
			text[0] = L"你确定你要回到主页吗？\n";
			but->button(273, 300, L"回到主页");
			if (but->putMessageBox(120, 165, 400, 150, L"回到主页", text, 1, MY_YESNO))		// 回到主页对话框
			{
				delete but;
				but = NULL;
				return 1;
			}
		}

		FlushBatchDraw();
		Sleep(5);
	}

	times = 0;
	delete but;
	but = NULL;
	return 0;
}

// 通过全关卡界面
void CAdventrue::gameOver()
{
	COther* but = new COther();

	while (1)
	{
		if (_kbhit())				// 键盘消息获取
			ch = _getch();

		while (MouseHit())			// 鼠标消息获取
			m_msg = GetMouseMsg();	

		but->putAll();				// 绘制背景

		for (int i = 0; i <= 3; i++)
		{
			settextcolor(RGB(100, 100, 100));
			settextstyle(52, 0, L"黑体");
			outtextxy(200 + i, 90 + i, L"游戏结束");
		}
		settextcolor(WHITE);
		settextstyle(52, 0, L"黑体");
		outtextxy(200 + 3, 90 + 3, L"游戏结束");	// 标题输出

		if (but->button(273, 215, L"回到主页"))		// 回到主页按钮
			break;

		if (but->button(273, 300, L"退出游戏"))		// 退出游戏按钮
		{
			delete but;
			but = NULL;
			EndBatchDraw();
			closegraph();
			exit(0);
		}

		FlushBatchDraw();
		Sleep(5);
	}

	delete but;
	but = NULL;
}

// 人物移动处理
void CAdventrue::man_Move()
{
	if (ch == 'w' && room[x - 1][y] != WALL)		// 上移处理
	{
		room[x - 1][y] = YOU;
		room[x][y] = ROAD;
		x--;
		ch = '#';									// 赋为其他值，防止人物持续移动
	}
	else if (ch == 's' && room[x + 1][y] != WALL)	// 下移处理
	{
		room[x + 1][y] = YOU;
		room[x][y] = ROAD;
		y++;
		ch = '#';
	}
	else if (ch == 'a' && room[x][y - 1] != WALL)	// 左移处理
	{
		room[x][y - 1] = YOU;
		room[x][y] = ROAD;
		y--;
		ch = '#';
	}
	else if (ch == 'd' && room[x][y + 1] != WALL)	// 右移处理
	{
		room[x][y + 1] = YOU;
		room[x][y] = ROAD;
		y++;
		ch = '#';
	}
}

// 清空数据处理
void CAdventrue::clear()
{
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			room[i][j] = 0;
			fmap[i][j] = 0;
		}
	}
	for (int i = 1; i <= (n + 1) / 2 * (m + 1) / 2; i++)
	{
		for (int j = 1; j <= (n + 1) / 2 * (m + 1) / 2; j++)
		{
			reg[i][j] = 0;
			feg[i][j] = 0;
		}
	}
	for (int i = 1; i <= (n + 1) / 2 * (m + 1) / 2; i++)
	{
		for (int j = 0; j < 3; j++)
			flag[j][i] = 0;
		tip[i] = 0;
	}
}

// 暴力 DFS 搜索生成迷宫核心
int CAdventrue::search(int x, int y)
{
	const int f[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}}; // 方向数组

	int e[4];												// 随机方向数组

	for (int i = 0; i < 4; i++)								// 随机化
	{
		e[i] = rand() % 4;
		for (int j = 0; j < i; j++)
		{
			if (e[i] == e[j])
			{
				e[i] = rand() % 4;
				j = -1;
			}
		}
	}
	if (x == 1 || y == 1 || x == n || y == m || room[x][y] == ROAD || fmap[x][y] == 1)	// 越界（已打通）判断
		return 0;

	int back = 0;
	for (int i = 0; i <= 3; i++)
		if (room[x + f[i][0]][y + f[i][1]] == ROAD)
			back++;
	if (back >= 2)		// 判断是否成回路
	{
		back = 0;
		return 0;
	}

	room[x][y] = ROAD;	// 打通
	for (int i = 0; i <= 3; i++)
	{
		fmap[x][y] = 1; // 标记
		search(x + f[e[i]][0], y + f[e[i]][1]);
		fmap[x][y] = 0; // 回溯
	}

	return 0;
}

// 图论 DFS 搜索生成迷宫核心
int CAdventrue::dfs(int step)
{
	int e[4];
	for (int i = 0; i < 4; i++)
	{
		e[i] = rand() % 4 + 1;
		for (int j = 0; j < i; j++)
		{
			if (e[i] == e[j])
			{
				e[i] = rand() % 4 + 1;
				j = -1;
			}
		}
	}
	int a = 0, cst[5];
	a = cst[e[0]] = step + 1;
	if (a > tot) cst[e[0]] = step;
	a = cst[e[1]] = step - 1;
	if (a < 1) cst[e[1]] = step;
	a = cst[e[2]] = step + (n - 1) / 2;
	if (a > tot) cst[e[2]] = step;
	a = cst[e[3]] = step - (n - 1) / 2;
	if (a < 1) cst[e[3]] = step;												// 随机化

	for (int i = 1; i <= 4; i++)
	{
		if ((reg[step][cst[i]] == 1 || reg[cst[i]][step] == 1) && !tip[cst[i]]) // 打通（走过）判断
		{

			reg[step][cst[i]] = 2;												// 标记打通
			reg[cst[i]][step] = 2;												// 标记打通
			tip[cst[i]] = 1;													// 标记走过
			tip[step] = 1;														// 标记走过
			dfs(cst[i]);
		}
	}
	return 0;
}

// 辅助函数
int CAdventrue::my_line(int x_1, int y_1, int x_2, int y_2)
{
	if (x_1 == x_2)		// 连通处理
		room[x_1][(y_1 + y_2) / 2] = ROAD;
	else if (y_1 == y_2)
		room[(x_1 + x_2) / 2][y_1] = ROAD;
	return 0;
}