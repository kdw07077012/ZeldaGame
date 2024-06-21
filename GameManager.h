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
#include "Boss_Field.h"
#include "Ending_Field.h"
#include "EndingCredit_Field.h"

#include <vector>

enum GAMESTATE
{
	GAMESTATE_TITLE,
	GAMESTATE_MENU,
	GAMESTATE_START,
	GAMESTATE_INVENTORY,
	GAMESTATE_QUEST,
	GAMESTATE_Credit,
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
	Object* m_oStoreField;
	Object* m_oShoeField;
	Object* m_oDungeonField;
	Object* m_oBossField;
	Object* m_oQudingField;
	Object* m_oEnestSystem;
	Object* m_oEndingCreditField;
	Object* m_oHUD;
	Object* m_oPlayer;
	Object* m_oInventory;
	Object* m_oQuestSystem;
	Object* m_oEndingField;

	std::vector<Object*> objects;

	Field* m_Field;
	Store_Field*	m_StoreField;
	ShoeStroe_Field* m_ShoeStroe_Field;
	StoreRoom_Field* m_StoreRoom_Field;
	Dungeon_Field* m_Dungeon_Field;
	Boss_Field* m_Boss_Field;
	QuestSystem* m_QuestSystem;
	Ending_Field* m_EndingField;
	EndingCredit_Field* m_EndingCredit_Field;
	
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

	void SetGameState(GAMESTATE state) { m_eCurGameState = state; }
	Player* GetPlayer() { return m_Player; }
	POINT GetMousePos() const { return ptMouse; }
};

