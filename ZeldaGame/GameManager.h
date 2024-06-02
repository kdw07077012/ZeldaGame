#pragma once
#include "Menu.h"
#include "Title.h"
#include "BitMapManager.h"
#include "Field.h"
#include "HUD.h"
#include "Inventory.h"
enum GAMESTATE
{
	GAMESTATE_TITLE,
	GAMESTATE_MENU,
	GAMESTATE_START,
	GAMESTATE_INVENTORY,
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
	Object* m_oPlayer;


	HUD* m_HUD;
	Field* m_Field;
	BackGround* m_BackGround;
	Menu* m_Menu;
	Title* m_Title;
	Player* m_Player;
	Inventory* m_Ivnentory;
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
	bool FieldCollision(RECT rect);

	Player* GetPlayer() { return m_Player; }
	SIZE GetWindowSize() const { return WindowSize; }
	POINT GetMousePos() const { return ptMouse; }
};

