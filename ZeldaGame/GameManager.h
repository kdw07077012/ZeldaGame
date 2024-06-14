#pragma once
#include "Menu.h"
#include "Title.h"
#include "BitMapManager.h"
#include "Field.h"
#include "HUD.h"
#include "Inventory.h"
#include "Store_Field.h"
#include "ShoeStroe_Field.h"
#include "StoreRoom_Field.h"
#include "Dungeon_Field.h"

#include "QuestSystem.h"
#include "SnakeKill_Quest.h"
#include "ShoeHelp_Quest.h"

enum GAMESTATE
{
	GAMESTATE_TITLE,
	GAMESTATE_MENU,
	GAMESTATE_START,
	GAMESTATE_INVENTORY,
	GAMESTATE_QUEST,
};



class GameManager
{
private: 
	static GameManager* m_pThis; // 싱글톤 
	HDC m_hDC, backDC; // 메인DC 백버퍼 DC
	HWND m_hWnd;		// 핸들
	FieldType currentField; // 현재 게임 필드 

	GAMESTATE m_eCurGameState;
	SIZE	WindowSize;
	HBITMAP CreateDIBSectionRe(int width, int Height);

	Object* m_oMenu;
	Object* m_oTitle;
	Object* m_oPlayer;

	Field* m_Field;
	Store_Field*	m_StoreField;
	ShoeStroe_Field* m_ShoeStroe_Field;
	StoreRoom_Field* m_StoreRoom_Field;
	Dungeon_Field* m_Dungeon_Field;
	QuestSystem* m_QuestSystem;
	
	HUD* m_HUD;
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
	bool FieldObject_AttackCollision(RECT rect);
	void NextField(FieldType Field);
	void StoreItemBuy(InGame_Item itemType, int price);
	void useItem(InGame_Item itemType);

	void Quest_OnNotify(QuestType type);
	void Quest_Add(Quest* quest);

	Player* GetPlayer() { return m_Player; }
	SIZE  GetWindowSize() const { return WindowSize; }
	POINT GetMousePos() const { return ptMouse; }
};

