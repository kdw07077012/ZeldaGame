#include "Menu.h"

Menu::Menu()
{
	m_currSelectMenu = SelectMenu_START;
	m_BitMap = BitMapManager::GetInstance()->GetBitMap(ImageType_Menu);
	m_SelectMenuBitmap = BitMapManager::GetInstance()->GetBitMap(ImageType_Button);

	for (int i = 0; i < SelectMenu_End; i++)
	{
		buttonPos[i].X = Default_ButtonX;
		buttonPos[i].Y = Default_ButtonY * (i + 1);
	}	

	m_SButtonSize = m_SelectMenuBitmap[0].GetSize();
	m_SButtonSize.cy /= 2;
	Button_sizMult = 2.0f;
	DrawCount = 0;
}

Menu::~Menu()
{
}

void Menu::Draw(HDC backDC, float DeltaTime)
{

	fDrawDeltaTime += DeltaTime;
	

	if (fDrawDeltaTime > 0.1f)
	{
		DrawCount++;
		if (DrawCount > 3)
			DrawCount = 0;
		
		fDrawDeltaTime = 0.0f;
	}


	m_BitMap[0].Draw(backDC, -720 * DrawCount, 0, 0); // 바탕 드로우
	

	


	switch (m_currSelectMenu)
	{
	case SelectMenu_START:
		if (!m_bEnableButton) {
			m_SelectMenuBitmap[SelectMenu_START].CutDraw(backDC, buttonPos[SelectMenu_START].X, buttonPos[SelectMenu_START].Y, 0, 0, m_SButtonSize, Button_sizMult);
		}
		m_SelectMenuBitmap[SelectMenu_QUIT + 1].CutDraw(backDC, buttonPos[SelectMenu_QUIT].X, buttonPos[SelectMenu_QUIT].Y, 0, 0, m_SButtonSize, Button_sizMult);
		break;
	case SelectMenu_QUIT:
		if (!m_bEnableButton) {
			m_SelectMenuBitmap[SelectMenu_QUIT + 1].CutDraw(backDC, buttonPos[SelectMenu_QUIT].X, buttonPos[SelectMenu_QUIT].Y, 0, 0, m_SButtonSize, Button_sizMult);
		}

		m_SelectMenuBitmap[SelectMenu_START].CutDraw(backDC, buttonPos[SelectMenu_START].X, buttonPos[SelectMenu_START].Y, 0, 0, m_SButtonSize, Button_sizMult);
		break;
	default:
		break;
	}

	if (m_bEnableButton) // 버튼이 활성화
		m_SelectMenuBitmap[m_currSelectMenu != SelectMenu_START ? 2 : 0].CutDraw(backDC, buttonPos[m_currSelectMenu].X, buttonPos[m_currSelectMenu].Y, 0, 25, m_SButtonSize, Button_sizMult);
	



	
	
}

void Menu::Update(float DeltaTime)
{
	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000 && m_bEnableButton)
	{
		

		switch (m_currSelectMenu)
		{
		case SelectMenu_START:
			break;
		case SelectMenu_QUIT:
			break;
		}


	}
}

void Menu::MenuSelect(POINT mousePos) //마우스 커서가 버튼 위에 올라와있는지 체크
{
	//std::string integerVal = std::to_string(m_posX.x);
	//메세지로 출력
	//MessageBoxA(NULL, integerVal.c_str(), NULL, MB_OK);

	if (mousePos.x > Default_ButtonX && m_SelectMenuBitmap[0].GetSize().cx * Button_sizMult + Default_ButtonX  > mousePos.x)
	{
		if (mousePos.y > buttonPos[SelectMenu_START].Y && m_SelectMenuBitmap[0].GetSize().cy * Button_sizMult + buttonPos[SelectMenu_START].Y > mousePos.y)
		{
			m_bEnableButton = true;
			m_currSelectMenu = SelectMenu_START;
		}
		else if (mousePos.y > buttonPos[SelectMenu_QUIT].Y && m_SelectMenuBitmap[0].GetSize().cy * Button_sizMult + buttonPos[SelectMenu_QUIT].Y > mousePos.y)
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
