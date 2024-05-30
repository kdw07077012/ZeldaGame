#pragma once
#include "Object.h"

#define Default_ButtonX 100
#define Default_ButtonY 100

enum SelectMenu
{
	SelectMenu_START,
	SelectMenu_EDIT,
	SelectMenu_QUIT,
	SelectMenu_End,
};


class Menu : public Object
{
public:
	Menu();
	~Menu();

	SelectMenu m_currSelectMenu;		 // 현재 메뉴 선택
	BitMap* m_SelectMenuBitmap;			 // 선택 메뉴 버튼 비트맵
	Position buttonPos[SelectMenu_End]; // 버튼별로 위치 
	SIZE m_SButtonSize;				     // 버튼 하나 크기별로 자르기위해 사이즈 사용
	bool m_bEnableButton = false;        // 버튼이 활성화 되있는지 
	float Button_sizMult; // 버튼 크기 배수

	int DrawCount;
	float fDrawDeltaTime;
	virtual void Draw(HDC backDC, float DeltaTime) override;
	void Update(float DeltaTime);
	void MenuSelect(POINT mousePos);

	virtual void Reset() override;
};

