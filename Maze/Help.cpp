// Help.cpp : ������Ϣ��ʵ���ļ�

#include "Game.h"		// ��Ϸͷ�ļ�

// ȫ�ֱ���

extern MOUSEMSG m_msg;	// �����Ϣ

// CHelp �ຯ��ʵ��

// ���ƽ���
void CHelp::put()
{
	COther* but = new COther();

	while (1)
	{

		while (MouseHit())							// �����Ϣ��ȡ
			m_msg = GetMouseMsg();

		but->putAll();								// ���Ʊ���

		for (int i = 0; i <= 3; i++)
		{
			settextcolor(RGB(100, 100, 100));
			settextstyle(52, 0, L"����");
			outtextxy(250 + i, 30 + i, L"�� ��");
		}
		settextcolor(WHITE);
		settextstyle(52, 0, L"����");
		outtextxy(250 + 3, 30 + 3, L"�� ��");		// �������

		setfillcolor(RGB(100, 100, 100));
		setlinecolor(BLACK);
		setlinestyle(PS_SOLID, 5);
		fillrectangle(125, 120, 510, 360);			// ���Ʊ߿�


		LOGFONT f;
		gettextstyle(&f);
		f.lfHeight = 25;
		wcscpy_s(f.lfFaceName, L"΢���ź� Light");
		f.lfQuality = ANTIALIASED_QUALITY;
		settextstyle(&f);			
		settextcolor(WHITE);
		outtextxy(140, 130, L"��Ϸ��ʼѡ��ϵ�йؿ�");
		outtextxy(140, 170, L"������ϵ�У�");
		outtextxy(140, 200, L"ɭ�֣��򵥣����� Prim �㷨��");
		outtextxy(140, 230, L"���Σ��еȣ�����ͼ�� DFS �㷨��");
		outtextxy(140, 260, L"���������ѣ����ڱ��� DFS �㷨��");
		outtextxy(140, 290, L"ѡ��ϵ�к󣬽�����Ϸ");
		outtextxy(140, 320, L"WSAD �������ң���Ϸ���м�ʱ��");	// ��Ϣ���

		if (but->button(280, 400, L"�ص���ҳ"))					// �ص���ҳ��ť
			break;

		FlushBatchDraw();
	}

	delete but;
	but = NULL;
}

//////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////