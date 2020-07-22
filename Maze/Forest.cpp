// Forest.cpp : 冒险模式-森林系列类实现文件

#include "Game.h"		// 游戏头文件

// 全局变量

extern char ch;						// 键盘消息
extern long long times, start_time;	// 计时器
extern MOUSEMSG m_msg;				// 鼠标消息

// CForest 函数实现

// 冒险模式-森林系列核心
void CForest::game()
{
	COther* but = new COther();

	while (1)
	{
		clear();									// 清空数据

		prim();										// 生成迷宫

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

			setfillcolor(RGB(100, 100, 100));
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

		if (winPut())			// 通过一关卡界面
			break;

		if (pass == all_pass)	// 通过全关卡界面
		{
			gameOver();
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

// Prim 随机生成迷宫
void CForest::prim()
{
	struct Arr						// 边结构体
	{
		int head, tail;
	};

	tot = 0;						// 节点数清空
	std::vector <Arr> ar;			// 存边

	for (int i = 1; i <= n; i++)	// 初始化
	{
		for (int j = 1; j <= m; j++)
		{
			if (i % 2 == 0 && j % 2 == 0 && i != n && j != m)
			{
				room[i][j] = ROAD;
				flag[0][++tot] = tot;
				flag[1][tot] = i;
				flag[2][tot] = j;
			}
			else
			{
				room[i][j] = WALL;
			}
		}
	}
	for (int i = 1; i <= tot; i++)
	{
		for (int j = 1; j <= tot; j++)
		{
			reg[i][j] = INF;
			feg[i][j] = INF;
		}
	}
	for (int i = 1; i <= tot; i++)
	{
		tip[i] = 0;
		if (i % ((n - 1) / 2) != 0)
		{
			feg[i][i + 1] = 1;
			feg[i + 1][i] = 1;
		}
		if (i <= tot - (n - 1) / 2)
		{
			feg[i][i + (n - 1) / 2] = 1;
			feg[i + (n - 1) / 2][i] = 1;
		}
	}
	for (int i = 1; i <= tot; i++)
	{
		if (feg[1][i] == 1)
		{
			Arr afo;
			afo.head = i;
			afo.tail = 1;
			ar.push_back(afo);
		}
	}

	tip[1] = 1;
	for (int i = 1; i <= tot - 1; i++)	// Prim 算法核心
	{
		std::random_shuffle(ar.begin(), ar.end());
		Arr ans;
		while (1) {
			ans = ar.back();
			if (tip[ans.head] && tip[ans.tail])
			{
				ar.pop_back();
			} else {
				break;
			}
		}
		ar.pop_back();
		tip[ans.head] = 1;
		tip[ans.tail] = 1;
		reg[ans.tail][ans.head] = 1;
		reg[ans.head][ans.tail] = 1;	// 随机选边并标记

		for (int j = 1; j <= tot; j++)	// 加入侯选边
		{
			if (feg[ans.head][j] == 1 && !tip[j])
			{
				Arr afo;
				afo.head = j;
				afo.tail = ans.head;
				ar.push_back(afo);
			}
		}
	}

	for (int i = 1; i <= tot; i++)
	{
		for (int j = 1; j <= tot; j++)
		{
			if (reg[i][j] == 1)
			{
				my_line(flag[1][i], flag[2][i], flag[1][j], flag[2][j]);
			}
		}
	}
	room[2][2] = YOU;
	room[n - 1][m] = END;	// 将 Prim 结果显示到迷宫中
}

// 绘制界面
void CForest::putRoom()
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
				setfillcolor(RGB(0, 100, 0));
				solidrectangle((j - 1 - y) * 50 + 266, (i - 1 - x) * 50 + 266, (j - y) * 50 + 265, (i - x) * 50 + 265);
			}
			else if (room[i][j] == ROAD)
			{
				setfillcolor(BROWN);
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
				setfillcolor(BROWN);
				solidrectangle((j - 1 - y) * 50 + 266, (i - 1 - x) * 50 + 266, (j - y) * 50 + 265, (i - x) * 50 + 265);
				setfillcolor(YELLOW);
				solidellipse((j - 1 - y) * 50 + 266, (i - 1 - x) * 50 + 266, (j - y) * 50 + 265, (i - x) * 50 + 265);
				x = i;
				y = j;
			}
		}
	}
}
