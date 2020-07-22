// Other.cpp : 刷新界面、放置按钮、输出对话框类实现文件

#include "Game.h"		// 游戏头文件

// 全局变量

extern char ch;			// 键盘消息
extern MOUSEMSG m_msg;	// 鼠标消息

// COtner 类函数实现

// 绘制背景
void COther::putAll()
{
	setbkcolor(RGB(50, 50, 50));
	cleardevice();
}

// 放置按钮
bool COther::button(int a, int b, wchar_t str[])
{
	static int x, y;																// 鼠标坐标

	setfillcolor(RGB(100, 100, 100));
	solidrectangle(a - 25, b, a + 19 * wcslen(str) + 25, b + 30);					// 绘制边框

	x = m_msg.x;
	y = m_msg.y;																	// 获取坐标

	if (x > a - 25 && (size_t)x < a + 19 * wcslen(str) + 25 && y > b && y < b + 30) // 获得焦点显示
	{
		setfillcolor(RGB(150, 150, 150));
		solidrectangle(a - 25, b, a + 19 * wcslen(str) + 25, b + 30);

		if (m_msg.uMsg == WM_LBUTTONUP)
		{
			m_msg.uMsg = WM_MOUSEMOVE;

			return 1;
		}
	}

	LOGFONT f;
	gettextstyle(&f);
	f.lfHeight = 25;
	wcscpy_s(f.lfFaceName, L"微软雅黑 Light");
	f.lfQuality = ANTIALIASED_QUALITY;
	settextstyle(&f);
	settextcolor(WHITE);
	outtextxy(a, b + 3, str);	// 输出文字

	return 0;
}

// 绘制对话框
int COther::putMessageBox(int x, int y, int wight, int hight, wchar_t title[], wchar_t * text[], int g_num, int var)
{
	setbkmode(TRANSPARENT);

	while (1)
	{
		if (_kbhit())								// 键盘消息清空
			ch = _getch();

		while (MouseHit())
			m_msg = GetMouseMsg();					// 鼠标消息获取

		setfillcolor(RGB(25, 25, 25));
		solidrectangle(x, y, x + wight, y + hight); // 绘制边框

		LOGFONT f;
		gettextstyle(&f);
		f.lfHeight = 30;
		wcscpy_s(f.lfFaceName, L"黑体");
		f.lfQuality = ANTIALIASED_QUALITY;
		settextstyle(&f);
		outtextxy(x + 20, y + 10, title);
		for (int i = 0; i < g_num; i++)				// 输出标题（正文）
		{
			f.lfHeight = 18;
			f.lfQuality = ANTIALIASED_QUALITY;
			settextstyle(&f);
			outtextxy(x + 20, y + 45 + i * 20, text[i]);
		}

		if (var == MY_OK)							// 按钮放置
		{
			if (button(x + wight - 70, y + hight - 37, L"确定"))
				return 0;
		}
		else if (var == MY_YESNO)
		{
			if (button(x + wight - 125, y + hight - 37, L"是"))
				return 1;

			if (button(x + wight - 50, y + hight - 37, L"否"))
				return 0;
		}
		FlushBatchDraw();
	}
	return 0;
}