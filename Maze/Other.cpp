// Other.cpp : ˢ�½��桢���ð�ť������Ի�����ʵ���ļ�

#include "Game.h"		// ��Ϸͷ�ļ�

// ȫ�ֱ���

extern char ch;			// ������Ϣ
extern MOUSEMSG m_msg;	// �����Ϣ

// COtner �ຯ��ʵ��

// ���Ʊ���
void COther::putAll()
{
	setbkcolor(RGB(50, 50, 50));
	cleardevice();
}

// ���ð�ť
bool COther::button(int a, int b, wchar_t str[])
{
	static int x, y;																// �������

	setfillcolor(RGB(100, 100, 100));
	solidrectangle(a - 25, b, a + 19 * wcslen(str) + 25, b + 30);					// ���Ʊ߿�

	x = m_msg.x;
	y = m_msg.y;																	// ��ȡ����

	if (x > a - 25 && (size_t)x < a + 19 * wcslen(str) + 25 && y > b && y < b + 30) // ��ý�����ʾ
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
	wcscpy_s(f.lfFaceName, L"΢���ź� Light");
	f.lfQuality = ANTIALIASED_QUALITY;
	settextstyle(&f);
	settextcolor(WHITE);
	outtextxy(a, b + 3, str);	// �������

	return 0;
}

// ���ƶԻ���
int COther::putMessageBox(int x, int y, int wight, int hight, wchar_t title[], wchar_t * text[], int g_num, int var)
{
	setbkmode(TRANSPARENT);

	while (1)
	{
		if (_kbhit())								// ������Ϣ���
			ch = _getch();

		while (MouseHit())
			m_msg = GetMouseMsg();					// �����Ϣ��ȡ

		setfillcolor(RGB(25, 25, 25));
		solidrectangle(x, y, x + wight, y + hight); // ���Ʊ߿�

		LOGFONT f;
		gettextstyle(&f);
		f.lfHeight = 30;
		wcscpy_s(f.lfFaceName, L"����");
		f.lfQuality = ANTIALIASED_QUALITY;
		settextstyle(&f);
		outtextxy(x + 20, y + 10, title);
		for (int i = 0; i < g_num; i++)				// ������⣨���ģ�
		{
			f.lfHeight = 18;
			f.lfQuality = ANTIALIASED_QUALITY;
			settextstyle(&f);
			outtextxy(x + 20, y + 45 + i * 20, text[i]);
		}

		if (var == MY_OK)							// ��ť����
		{
			if (button(x + wight - 70, y + hight - 37, L"ȷ��"))
				return 0;
		}
		else if (var == MY_YESNO)
		{
			if (button(x + wight - 125, y + hight - 37, L"��"))
				return 1;

			if (button(x + wight - 50, y + hight - 37, L"��"))
				return 0;
		}
		FlushBatchDraw();
	}
	return 0;
}