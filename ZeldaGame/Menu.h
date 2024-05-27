#pragma once
#include "Object.h"

#define Default_ButtonX 200
#define Default_ButtonY 100

enum SelectMenu
{
	SelectMenu_START,
	SelectMenu_EDIT,
	SelectMenu_QUIT,
	SelectMenu_End,
};

struct ButtonPos
{
	int posX;
	int PosY;
};

class Menu : public Object
{
public:
	Menu();
	~Menu();

	SelectMenu m_currSelectMenu;		 // ���� �޴� ����
	BitMap* m_SelectMenuBitmap;			 // ���� �޴� ��ư ��Ʈ��
	ButtonPos buttonPos[SelectMenu_End]; // ��ư���� ��ġ 
	SIZE m_SButtonSize;				     // ��ư �ϳ� ũ�⺰�� �ڸ������� ������ ���
	bool m_bEnableButton = false;        // ��ư�� Ȱ��ȭ ���ִ��� 
	

	virtual void Draw(HDC backDC, float DeltaTime) override;
	void Update(float DeltaTime);
	void MenuSelect(POINT mousePos);

	virtual void Reset() override;
};

