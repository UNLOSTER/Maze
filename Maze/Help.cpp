// Help.cpp : 帮助信息类实现文件

#include "Game.h"		// 游戏头文件

// 全局变量

extern MOUSEMSG m_msg;	// 鼠标消息

// CHelp 类函数实现

// 绘制界面
void CHelp::put()
{
	COther* but = new COther();

	while (1)
	{

		while (MouseHit())							// 鼠标消息获取
			m_msg = GetMouseMsg();

		but->putAll();								// 绘制背景

		for (int i = 0; i <= 3; i++)
		{
			settextcolor(RGB(100, 100, 100));
			settextstyle(52, 0, L"黑体");
			outtextxy(250 + i, 30 + i, L"帮 助");
		}
		settextcolor(WHITE);
		settextstyle(52, 0, L"黑体");
		outtextxy(250 + 3, 30 + 3, L"帮 助");		// 标题输出

		setfillcolor(RGB(100, 100, 100));
		setlinecolor(BLACK);
		setlinestyle(PS_SOLID, 5);
		fillrectangle(125, 120, 510, 360);			// 绘制边框


		LOGFONT f;
		gettextstyle(&f);
		f.lfHeight = 25;
		wcscpy_s(f.lfFaceName, L"微软雅黑 Light");
		f.lfQuality = ANTIALIASED_QUALITY;
		settextstyle(&f);			
		settextcolor(WHITE);
		outtextxy(140, 130, L"游戏开始选择系列关卡");
		outtextxy(140, 170, L"有三种系列：");
		outtextxy(140, 200, L"森林（简单，基于 Prim 算法）");
		outtextxy(140, 230, L"地牢（中等，基于图论 DFS 算法）");
		outtextxy(140, 260, L"地狱（困难，基于暴力 DFS 算法）");
		outtextxy(140, 290, L"选择系列后，进入游戏");
		outtextxy(140, 320, L"WSAD 上下左右，游戏中有计时器");	// 信息输出

		if (but->button(280, 400, L"回到主页"))					// 回到主页按钮
			break;

		FlushBatchDraw();
	}

	delete but;
	but = NULL;
}

//////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////