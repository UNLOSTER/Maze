// Game.h : ��Ϸ��ͷ�ļ�

#pragma once		// ��ֹ��ͷ�ļ�����ε���

#include "Maze.h"	// ��ʼ��ͷ�ļ�

// ��Ϸ��

// ˢ�½��桢���ð�ť������Ի�����
class COther
{
public:
	COther() {}
	~COther() {}
	
	void putAll();																											// ���Ʊ���
	bool button(int a, int b, wchar_t str[]);																				// ���ð�ť
	int putMessageBox(int x, int y, int wight, int hight, wchar_t title[], wchar_t * text[], int g_num, int var = MY_OK);	// ����Ի���
};

// ð��ģʽ��
class CAdventrue
{
public:
	int pass, all_pass;												// �ؿ����ܹؿ�
	int to_x, to_y, x, y, room[150][150], n, m;						// �յ����ꡢ�������ꡢ�Թ���ͼ������Թ���С
	int tot, reg[2600][2600], feg[2600][2600], flag[3][2600];	// ͼ�ڵ��������ڽӾ��󡢸����ڽӾ�����Թ���������ͼ�ڵ��Ź�ϵ��¼
	bool fmap[150][150], tip[2600];								// �����Թ���ͼ��ͼ�ڵ��Ƿ��߹���¼
	
	CAdventrue() {}
	~CAdventrue() {}
	
	virtual void game();									// ��ģʽ��ϵ�У�����

	bool winPut();											// ͨ��һ�ؿ�����
	void gameOver();										// ͨ��ȫ�ؿ�����
	void man_Move();										// �����ƶ�����
	void clear();											// ������ݴ���

	int search(int x, int y);								// DFS ���������Թ�����
	int dfs(int step);										// ͼ�� DFS ���������Թ�����
	int my_line(int x_1, int y_1, int x_2, int y_2);		// ��������
};

// ð��ģʽ-ɭ��ϵ����
class CForest : public CAdventrue
{
public:
	CForest() {}
	~CForest() {}
	
	void game();	// ��ģʽ��ϵ�У�����

private:
	void prim();	// Prim ��������Թ�
	void putRoom();	// ���ƽ���
};

// ð��ģʽ-����ϵ����
class CDungeon : public CAdventrue
{
public:
	CDungeon() {}
	~CDungeon() {}
	
	void game();	// ��ģʽ��ϵ�У�����

private:
	void deepFS();	// ͼ�� DFS ��������Թ�
	void putRoom(); // ���ƽ���
};

// ð��ģʽ-����ϵ����
class CInfernal : public CAdventrue
{
public:
	CInfernal() {}
	~CInfernal() {}
	
	void game();	// ��ģʽ��ϵ�У�����

private:
	void myKLS();	// ���� DFS ��������Թ�
	void putRoom(); // ���ƽ���
};

// ������Ϣ��
class CHelp
{
public:
	CHelp() {}
	~CHelp() {}
	
	void put();		// ���ƽ���
};
