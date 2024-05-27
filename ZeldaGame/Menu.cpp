#include "Menu.h"

Menu::Menu()
{
	m_currSelectMenu = SelectMenu_START;
	m_BitMap = BitMapManager::GetInstance()->GetBitMap(ImageType_Menu);
	m_SelectMenuBitmap = BitMapManager::GetInstance()->GetBitMap(ImageType_Button);

	for (int i = 0; i < SelectMenu_End; i++)
	{
		buttonPos[i].posX = Default_ButtonX;
		buttonPos[i].PosY = Default_ButtonY * (i + 1);
	}	

	m_SButtonSize = m_SelectMenuBitmap[0].GetSize();
	m_SButtonSize.cy /= 2;
}

Menu::~Menu()
{
}

void Menu::Draw(HDC backDC, float DeltaTime)
{
	m_BitMap[0].Draw(backDC, 0, 0, 0); // 바탕 드로우

	


	switch (m_currSelectMenu)
	{
	case SelectMenu_START:
		if (!m_bEnableButton) {
			m_SelectMenuBitmap[SelectMenu_START].CutDraw(backDC, buttonPos[SelectMenu_START].posX, buttonPos[SelectMenu_START].PosY, 0, 0, m_SButtonSize);
		}
		m_SelectMenuBitmap[SelectMenu_EDIT].CutDraw(backDC, buttonPos[SelectMenu_EDIT].posX, buttonPos[SelectMenu_EDIT].PosY, 0, 0, m_SButtonSize);
		m_SelectMenuBitmap[SelectMenu_QUIT].CutDraw(backDC, buttonPos[SelectMenu_QUIT].posX, buttonPos[SelectMenu_QUIT].PosY, 0, 0, m_SButtonSize);
		break;
	case SelectMenu_EDIT:
		if (!m_bEnableButton) {
			m_SelectMenuBitmap[SelectMenu_EDIT].CutDraw(backDC, buttonPos[SelectMenu_EDIT].posX, buttonPos[SelectMenu_EDIT].PosY, 0, 0, m_SButtonSize);
		}

		m_SelectMenuBitmap[SelectMenu_START].CutDraw(backDC, buttonPos[SelectMenu_START].posX, buttonPos[SelectMenu_START].PosY, 0, 0, m_SButtonSize);
		m_SelectMenuBitmap[SelectMenu_QUIT].CutDraw(backDC, buttonPos[SelectMenu_QUIT].posX, buttonPos[SelectMenu_QUIT].PosY, 0, 0, m_SButtonSize);
		break;
	case SelectMenu_QUIT:
		if (!m_bEnableButton) {
			m_SelectMenuBitmap[SelectMenu_QUIT].CutDraw(backDC, buttonPos[SelectMenu_QUIT].posX, buttonPos[SelectMenu_QUIT].PosY, 0, 0, m_SButtonSize);
		}

		m_SelectMenuBitmap[SelectMenu_START].CutDraw(backDC, buttonPos[SelectMenu_START].posX, buttonPos[SelectMenu_START].PosY, 0, 0, m_SButtonSize);
		m_SelectMenuBitmap[SelectMenu_EDIT].CutDraw(backDC, buttonPos[SelectMenu_EDIT].posX, buttonPos[SelectMenu_EDIT].PosY, 0, 0, m_SButtonSize);
		break;
	default:
		break;
	}

	if (m_bEnableButton) // 버튼이 활성화
		m_SelectMenuBitmap[m_currSelectMenu].CutDraw(backDC, buttonPos[m_currSelectMenu].posX, buttonPos[m_currSelectMenu].PosY, 0, 25, m_SButtonSize);
	



	
	
}

void Menu::Update(float DeltaTime)
{
	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000 && m_bEnableButton)
	{
		//std::string integerVal = std::to_string(0);
		// 메세지로 출력
		//MessageBoxA(NULL, integerVal.c_str(), NULL, MB_OK);

		switch (m_currSelectMenu)
		{
		case SelectMenu_START:
			break;
		case SelectMenu_EDIT:
			break;
		case SelectMenu_QUIT:
			break;
		}


	}
}

void Menu::MenuSelect(POINT mousePos)
{

	if (mousePos.x > Default_ButtonX && m_SelectMenuBitmap[0].GetSize().cx + Default_ButtonX > mousePos.x)
	{
		if (mousePos.y > buttonPos[SelectMenu_START].PosY && m_SelectMenuBitmap[0].GetSize().cy + buttonPos[SelectMenu_START].PosY > mousePos.y)
		{
			m_bEnableButton = true;
			m_currSelectMenu = SelectMenu_START;
		}
		else if (mousePos.y > buttonPos[SelectMenu_EDIT].PosY && m_SelectMenuBitmap[0].GetSize().cy + buttonPos[SelectMenu_EDIT].PosY > mousePos.y)
		{
			m_bEnableButton = true;
			m_currSelectMenu = SelectMenu_EDIT;
		}
		else if (mousePos.y > buttonPos[SelectMenu_QUIT].PosY && m_SelectMenuBitmap[0].GetSize().cy + buttonPos[SelectMenu_QUIT].PosY > mousePos.y)
		{
			m_bEnableButton = true;
			m_currSelectMenu = SelectMenu_QUIT;
		}
	}
	else
	{
		m_bEnableButton = false;
	}

}

void Menu::Reset()
{
}
