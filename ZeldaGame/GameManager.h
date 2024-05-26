#pragma once
#include "Menu.h"
#include "Title.h"
#include "BitMapManager.h"

class GameManager
{
private: 
	static GameManager* m_pThis; // 싱글톤 
	HDC m_hDC, backDC; // 메인DC 백버퍼 DC
	HWND m_hWnd;		// 핸들

	GAMESTATE m_eCurGameState;
	SIZE	WindowSize;
	HBITMAP CreateDIBSectionRe(int width, int Height);

	Object* m_oMenu;
	Object* m_oTitle;

	Menu* m_Menu;
	Title* m_Title;

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
};

