#include <Windows.h>
#include "auto_fly.h"



LONG CALLBACK BackGroundWindowProc(
	HWND hwnd, //
	UINT msg, // ��Ϣ
	WPARAM wParam, // ��Ϣ��������ͬ����Ϣ�в�ͬ�����壬���MSDN��ÿ����Ϣ���ĵ�
	LPARAM lParam); // ��Ϣ��������ͬ����Ϣ�в�ͬ�����壬���MSDN��ÿ����Ϣ���ĵ�


BOOL BackGroundWindwowRegister(HINSTANCE hinstance);

HWND BackgroundWindowCreate(HINSTANCE hinstance);

LONG CALLBACK FightWindowProc(
	HWND hwnd, //
	UINT msg, // ��Ϣ
	WPARAM wParam, // ��Ϣ��������ͬ����Ϣ�в�ͬ�����壬���MSDN��ÿ����Ϣ���ĵ�
	LPARAM lParam); // ��Ϣ��������ͬ����Ϣ�в�ͬ�����壬���MSDN��ÿ����Ϣ���ĵ�

LONG FighterCreate(HWND hwnd);
HWND FightWindowCreate(HINSTANCE hinstance);

BOOL FightWindowRegister(HINSTANCE hinstance);


LONG BackgroundCreate(HWND hwnd);


LONG BackgroundResizeAndMove(HWND hwnd, LPRECT lpRect);
LONG BackgroundPaint(HWND hwnd);
LONG OnKeydown(HWND hwnd, UINT vk);