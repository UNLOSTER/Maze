// Infernal.cpp : ð��ģʽ-����ϵ����ʵ���ļ�

#include "Game.h"		// ��Ϸͷ�ļ�

// ȫ�ֱ���

extern char ch;						// ������Ϣ
extern long long times, start_time;	// ��ʱ��
extern MOUSEMSG m_msg;				// �����Ϣ

// CInfernal ����ʵ��

// ð��ģʽ-����ϵ����
void CInfernal::game()
{
	COther* but = new COther();

	while (1)
	{
		clear();									// �������

		myKLS();									// �����Թ�
		
		x = 2;
		y = 2;										// ��������

		start_time = int(time(NULL));				// ���ó�ʼʱ�� 0 
		
		while (1)
		{
			times = int(time(NULL)) - start_time;	// �ۼ�ʱ��

			ch = '#';								// ������Ϣ���

			if (_kbhit())							// ������Ϣ��ȡ
				ch = _getch();

			while (MouseHit())						// �����Ϣ��ȡ
				m_msg = GetMouseMsg();

			man_Move();								// �����ƶ�����

			if (x == to_x && y == to_y)				// �����յ��ж�
				break;

			but->putAll();							// ���Ʊ���

			setfillcolor(RGB(50, 0, 0));
			solidrectangle(16, 17, 465, 465);		// ������Ϸ��

			putRoom();								// ���ƽ���

			if (but->button(513, 400, L"�ص���ҳ"))											// �ص���ҳ��ť
			{
				long long t = times;
				wchar_t* text[10];
				text[0] = L"���Ƿ�Ҫ�ص���ҳ��\n";
				but->button(513, 400, L"�ص���ҳ");
				but->button(513, 350, L"����ͣ��");
				if (but->putMessageBox(120, 165, 400, 150, L"�ص���ҳ", text, 1, MY_YESNO))	// �ص���ҳ�Ի���
				{
					delete but;
					but = NULL;
					return;
				}
				start_time = int(time(NULL)) - t;
				times = t;
			}

			if (but->button(513, 350, L"����ͣ��"))							// ��ͣ��ť
			{
				long long t = times;
				wchar_t* text[10];
				text[0] = L"����ȷ���������ͣ\n";
				but->button(513, 350, L"����ͣ��");
				but->putMessageBox(170, 165, 300, 150, L"��ͣ", text, 1);	// ��ͣ�Ի���
				start_time = int(time(NULL)) - t;
				times = t;
			}

			FlushBatchDraw();
			Sleep(5);
		}

		if (winPut())		// ͨ��һ�ؿ�����
			break;

		if (pass == all_pass)
		{
			gameOver();		// ͨ��ȫ�ؿ�����
			break;
		}
		pass++;
		n += 2;
		m += 2;
		if (n > 99 || m > 99)	// ��һ��
		{
			n = 99;
			m = 99;
		}
	}

	delete but;
	but = NULL;
}

// ���� DFS ��������Թ�
void CInfernal::myKLS()
{
	for (int i = 1; i <= n; i++)	// ��ʼ��
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
	room[n - 1][m - 2] = ROAD;		// ���� DFS ����
}

// ���ƽ���
void CInfernal::putRoom()
{
	wchar_t tim[25], pas1[50], pas2[50];	// ��ʱ����ǰ�ؿ����ܹؿ�

	swprintf_s(pas1, L"�� %d ��\0", pass);
	swprintf_s(pas2, L"�� %d ��\0", all_pass);
	swprintf_s(tim, L"ʹ��ʱ�� %lld s\0", times);
	LOGFONT f;
	gettextstyle(&f);
	f.lfHeight = 20;
	wcscpy_s(f.lfFaceName, L"����");
	f.lfQuality = ANTIALIASED_QUALITY;
	settextstyle(&f);
	settextcolor(WHITE);
	outtextxy(480, 25, pas1);
	outtextxy(480, 55, pas2);
	outtextxy(480, 85, tim);				// �������

	for (int i = x - 4; i <= x + 4; i++)	// �����Թ�
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
