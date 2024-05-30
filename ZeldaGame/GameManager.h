#pragma once
#include "Menu.h"
#include "Title.h"
#include "BitMapManager.h"
#include "Field.h"

enum GAMESTATE
{
	GAMESTATE_TITLE,
	GAMESTATE_MENU,
	GAMESTATE_START,
};


class GameManager
{
private: 
	static GameManager* m_pThis; // ½Ì±ÛÅæ 
	HDC m_hDC, backDC; // ¸ÞÀÎDC ¹é¹öÆÛ DC
	HWND m_hWnd;		// ÇÚµé

	GAMESTATE m_eCurGameState;
	SIZE	WindowSize;
	HBITMAP CreateDIBSectionRe(int width, int Height);

	Object* m_oMenu;
	Object* m_oTitle;
	Object* m_oBackGround;
	Object* m_oPlayer;

	Field* m_Field;
	BackGround* m_BackGround;
	Menu* m_Menu;
	Title* m_Title;
	Player* m_Player;
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

