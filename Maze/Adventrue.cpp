// Adventrue.cpp : ð��ģʽ���ļ�

#include "Game.h"	// ��Ϸͷ�ļ�

// ȫ�ֱ���

char ch;						// ������Ϣ
long long times, start_time;	// ��ʱ��
MOUSEMSG m_msg;				// �����Ϣ

// CAdventure �ຯ��ʵ��

// ð��ģʽ����
void CAdventrue::game()
{
	CAdventrue* Adv;
	CHelp* help = new CHelp();
	COther* but = new COther();

	setbkmode(TRANSPARENT);

	BeginBatchDraw();

	while (1)
	{
		if (_kbhit())		// ������Ϣ��ȡ
		{
			ch = _getch();	// ������Ϣ��ȡ
			if (ch == 27)	// �� Esc �˳�
			{
				break;
			}
		}

		while (MouseHit())	// �����Ϣ��ȡ
			m_msg = GetMouseMsg();

		but->putAll();		// ���Ʊ���

		for (int i = 0; i <= 3; i++)
		{
			settextcolor(RGB(100, 100, 100));
			settextstyle(70, 0, L"΢���ź�");
			outtextxy(235 + i, 85 + i, L"�ԡ���");
		}
		settextcolor(WHITE);
		settextstyle(70, 0, L"΢���ź�");
		outtextxy(235 + 3, 85 + 3, L"�ԡ���");		// �������

		if (but->button(280, 200, L"��ɭ�֡�"))		// ɭ��ϵ�а�ť
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

		if (but->button(280, 260, L"�����Ρ�"))		// ����ϵ�а�ť
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

		if (but->button(280, 320, L"��������"))		// ����ϵ�а�ť
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

		if (but->button(280, 380, L"��������"))		// ������Ϣ��ť
			help->put();

		LOGFONT f;
		gettextstyle(&f);
		f.lfWidth = 10;
		wcscpy_s(f.lfFaceName, L"΢���ź� Light");
		f.lfQuality = ANTIALIASED_QUALITY;
		settextstyle(&f);
		settextcolor(WHITE);

		outtextxy(340, 153, L"V1.0 By Lost");
		outtextxy(249, 440, L"�� Esc �˳���Ϸ");	// �������

		FlushBatchDraw();
		Sleep(5);
	}

	EndBatchDraw();

	delete but;
	but = NULL;
	delete Adv;
	Adv = NULL;
}

// ͨ��һ�ؿ�����
bool CAdventrue::winPut()
{
	COther* but = new COther();

	wchar_t title[50];

	swprintf_s(title, L"ʹ��ʱ�� %lld s\0", times);

	while (1)
	{
		if (_kbhit())				// ������Ϣ��ȡ
			ch = _getch();

		while (MouseHit())
			m_msg = GetMouseMsg();	// �����Ϣ��ȡ

		but->putAll();				// ���Ʊ���

		for (int i = 0; i <= 3; i++)
		{
			settextcolor(RGB(100, 100, 100));
			settextstyle(52, 0, L"����");
			outtextxy(140 + i, 90 + i, title);
		}
		settextcolor(WHITE);
		settextstyle(52, 0, L"����");
		outtextxy(140 + 3, 90 + 3, title);		// �������

		if (but->button(273, 215, L" ��һ��"))	// ��һ�ذ�ť
			break;

		if (but->button(273, 300, L"�ص���ҳ"))	// �ص���ҳ��ť
		{
			wchar_t* text[10];
			text[0] = L"��ȷ����Ҫ�ص���ҳ��\n";
			but->button(273, 300, L"�ص���ҳ");
			if (but->putMessageBox(120, 165, 400, 150, L"�ص���ҳ", text, 1, MY_YESNO))		// �ص���ҳ�Ի���
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

// ͨ��ȫ�ؿ�����
void CAdventrue::gameOver()
{
	COther* but = new COther();

	while (1)
	{
		if (_kbhit())				// ������Ϣ��ȡ
			ch = _getch();

		while (MouseHit())			// �����Ϣ��ȡ
			m_msg = GetMouseMsg();	

		but->putAll();				// ���Ʊ���

		for (int i = 0; i <= 3; i++)
		{
			settextcolor(RGB(100, 100, 100));
			settextstyle(52, 0, L"����");
			outtextxy(200 + i, 90 + i, L"��Ϸ����");
		}
		settextcolor(WHITE);
		settextstyle(52, 0, L"����");
		outtextxy(200 + 3, 90 + 3, L"��Ϸ����");	// �������

		if (but->button(273, 215, L"�ص���ҳ"))		// �ص���ҳ��ť
			break;

		if (but->button(273, 300, L"�˳���Ϸ"))		// �˳���Ϸ��ť
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

// �����ƶ�����
void CAdventrue::man_Move()
{
	if (ch == 'w' && room[x - 1][y] != WALL)		// ���ƴ���
	{
		room[x - 1][y] = YOU;
		room[x][y] = ROAD;
		x--;
		ch = '#';									// ��Ϊ����ֵ����ֹ��������ƶ�
	}
	else if (ch == 's' && room[x + 1][y] != WALL)	// ���ƴ���
	{
		room[x + 1][y] = YOU;
		room[x][y] = ROAD;
		y++;
		ch = '#';
	}
	else if (ch == 'a' && room[x][y - 1] != WALL)	// ���ƴ���
	{
		room[x][y - 1] = YOU;
		room[x][y] = ROAD;
		y--;
		ch = '#';
	}
	else if (ch == 'd' && room[x][y + 1] != WALL)	// ���ƴ���
	{
		room[x][y + 1] = YOU;
		room[x][y] = ROAD;
		y++;
		ch = '#';
	}
}

// ������ݴ���
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

// ���� DFS ���������Թ�����
int CAdventrue::search(int x, int y)
{
	const int f[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}}; // ��������

	int e[4];												// �����������

	for (int i = 0; i < 4; i++)								// �����
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
	if (x == 1 || y == 1 || x == n || y == m || room[x][y] == ROAD || fmap[x][y] == 1)	// Խ�磨�Ѵ�ͨ���ж�
		return 0;

	int back = 0;
	for (int i = 0; i <= 3; i++)
		if (room[x + f[i][0]][y + f[i][1]] == ROAD)
			back++;
	if (back >= 2)		// �ж��Ƿ�ɻ�·
	{
		back = 0;
		return 0;
	}

	room[x][y] = ROAD;	// ��ͨ
	for (int i = 0; i <= 3; i++)
	{
		fmap[x][y] = 1; // ���
		search(x + f[e[i]][0], y + f[e[i]][1]);
		fmap[x][y] = 0; // ����
	}

	return 0;
}

// ͼ�� DFS ���������Թ�����
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
	if (a < 1) cst[e[3]] = step;												// �����

	for (int i = 1; i <= 4; i++)
	{
		if ((reg[step][cst[i]] == 1 || reg[cst[i]][step] == 1) && !tip[cst[i]]) // ��ͨ���߹����ж�
		{

			reg[step][cst[i]] = 2;												// ��Ǵ�ͨ
			reg[cst[i]][step] = 2;												// ��Ǵ�ͨ
			tip[cst[i]] = 1;													// ����߹�
			tip[step] = 1;														// ����߹�
			dfs(cst[i]);
		}
	}
	return 0;
}

// ��������
int CAdventrue::my_line(int x_1, int y_1, int x_2, int y_2)
{
	if (x_1 == x_2)		// ��ͨ����
		room[x_1][(y_1 + y_2) / 2] = ROAD;
	else if (y_1 == y_2)
		room[(x_1 + x_2) / 2][y_1] = ROAD;
	return 0;
}