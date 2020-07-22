// Infernal.cpp : 冒险模式-地狱系列类实现文件

#include "Game.h"		// 游戏头文件

// 全局变量

extern char ch;						// 键盘消息
extern long long times, start_time;	// 计时器
extern MOUSEMSG m_msg;				// 鼠标消息

// CInfernal 函数实现

// 冒险模式-地狱系列类
void CInfernal::game()
{
	COther* but = new COther();

	while (1)
	{
		clear();									// 清空数据

		myKLS();									// 生成迷宫
		
		x = 2;
		y = 2;										// 重置坐标

		start_time = int(time(NULL));				// 设置初始时间 0 
		
		while (1)
		{
			times = int(time(NULL)) - start_time;	// 累加时间

			ch = '#';								// 键盘消息清空

			if (_kbhit())							// 键盘消息获取
				ch = _getch();

			while (MouseHit())						// 鼠标消息获取
				m_msg = GetMouseMsg();

			man_Move();								// 人物移动处理

			if (x == to_x && y == to_y)				// 到达终点判断
				break;

			but->putAll();							// 绘制背景

			setfillcolor(RGB(50, 0, 0));
			solidrectangle(16, 17, 465, 465);		// 绘制游戏区

			putRoom();								// 绘制界面

			if (but->button(513, 400, L"回到主页"))											// 回到主页按钮
			{
				long long t = times;
				wchar_t* text[10];
				text[0] = L"你是否要回到主页？\n";
				but->button(513, 400, L"回到主页");
				but->button(513, 350, L"　暂停　");
				if (but->putMessageBox(120, 165, 400, 150, L"回到主页", text, 1, MY_YESNO))	// 回到主页对话框
				{
					delete but;
					but = NULL;
					return;
				}
				start_time = int(time(NULL)) - t;
				times = t;
			}

			if (but->button(513, 350, L"　暂停　"))							// 暂停按钮
			{
				long long t = times;
				wchar_t* text[10];
				text[0] = L"按“确定”解除暂停\n";
				but->button(513, 350, L"　暂停　");
				but->putMessageBox(170, 165, 300, 150, L"暂停", text, 1);	// 暂停对话框
				start_time = int(time(NULL)) - t;
				times = t;
			}

			FlushBatchDraw();
			Sleep(5);
		}

		if (winPut())		// 通过一关卡界面
			break;

		if (pass == all_pass)
		{
			gameOver();		// 通过全关卡界面
			break;
		}
		pass++;
		n += 2;
		m += 2;
		if (n > 99 || m > 99)	// 下一关
		{
			n = 99;
			m = 99;
		}
	}

	delete but;
	but = NULL;
}

// 暴力 DFS 随机生成迷宫
void CInfernal::myKLS()
{
	for (int i = 1; i <= n; i++)	// 初始化
	{
		for (int j = 1; j <= m; j++)
		{
			room[i][j] = WALL;
		}
	}

	search(n - 1, m - 1);
	room[2][2] = YOU;
	room[n - 1][m] = END;
	room[2][3] = ROAD;
	room[3][2] = ROAD;
	room[n - 1][m - 1] = ROAD;
	room[n - 2][m - 1] = ROAD;
	room[n - 1][m - 2] = ROAD;		// 进行 DFS 生成
}

// 绘制界面
void CInfernal::putRoom()
{
	wchar_t tim[25], pas1[50], pas2[50];	// 计时、当前关卡和总关卡

	swprintf_s(pas1, L"第 %d 关\0", pass);
	swprintf_s(pas2, L"共 %d 关\0", all_pass);
	swprintf_s(tim, L"使用时间 %lld s\0", times);
	LOGFONT f;
	gettextstyle(&f);
	f.lfHeight = 20;
	wcscpy_s(f.lfFaceName, L"黑体");
	f.lfQuality = ANTIALIASED_QUALITY;
	settextstyle(&f);
	settextcolor(WHITE);
	outtextxy(480, 25, pas1);
	outtextxy(480, 55, pas2);
	outtextxy(480, 85, tim);				// 输出文字

	for (int i = x - 4; i <= x + 4; i++)	// 绘制迷宫
	{
		for (int j = y - 4; j <= y + 4; j++)
		{
			if (i < 1 || j < 1) {
				continue;
			}
			if (room[i][j] == WALL)
			{
				setfillcolor(RGB(100, 0, 0));
				solidrectangle((j - 1 - y) * 50 + 266, (i - 1 - x) * 50 + 266, (j - y) * 50 + 265, (i - x) * 50 + 265);
			}
			else if (room[i][j] == ROAD)
			{
				setfillcolor(RGB(200, 0, 0));
				solidrectangle((j - 1 - y) * 50 + 266, (i - 1 - x) * 50 + 266, (j - y) * 50 + 265, (i - x) * 50 + 265);
			}
			else if (room[i][j] == END)
			{
				setfillcolor(BLUE);
				solidrectangle((j - 1 - y) * 50 + 266, (i - 1 - x) * 50 + 266, (j - y) * 50 + 265, (i - x) * 50 + 265);
				to_x = i;
				to_y = j;
			}
			else if (room[i][j] == YOU)
			{
				setfillcolor(RGB(200, 0, 0));
				solidrectangle((j - 1 - y) * 50 + 266, (i - 1 - x) * 50 + 266, (j - y) * 50 + 265, (i - x) * 50 + 265);
				setfillcolor(YELLOW);
				solidellipse((j - 1 - y) * 50 + 266, (i - 1 - x) * 50 + 266, (j - y) * 50 + 265, (i - x) * 50 + 265);
				x = i;
				y = j;
			}
		}
	}
}
