#pragma once
#include "Menu.h"
#include "Title.h"
#include "BitMapManager.h"
#include "BackGround.h"

enum GAMESTATE
{
	GAMESTATE_TITLE,
	GAMESTATE_MENU,
	GAMESTATE_START,
};


class GameManager
{
private: 
	static GameManager* m_pThis; // �̱��� 
	HDC m_hDC, backDC; // ����DC ����� DC
	HWND m_hWnd;		// �ڵ�

	GAMESTATE m_eCurGameState;
	SIZE	WindowSize;
	HBITMAP CreateDIBSectionRe(int width, int Height);

	Object* m_oMenu;
	Object* m_oTitle;
	Object* m_oBackGround;

	BackGround* m_BackGround;
	Menu* m_Menu;
	Title* m_Title;
	POINT ptMouse;

public:
	static GameManager* GetInstance()
	{
		if (NULL == m_pThis)
			m_pThis = new GameManager;

		return m_pThis;
	}

	void Init(HWND hWnd);
	void Update(float DeltaTime);
	void DoubleBuffer(float DeltaTime);
	void Release(HWND hWnd);

	SIZE GetWindowSize() const { return WindowSize; }
	POINT GetMousePos() const { return ptMouse; }
};

