#include "Menu.h"

Menu::Menu()
{
	m_BitMap = BitMapManager::GetInstance()->GetBitMap(ImageType_Menu);
}

Menu::~Menu()
{
}

void Menu::Draw(HDC backDC, float DeltaTime)
{
	SIZE size = BitMapManager::GetInstance()->GetWindowSize();
	const int& TitleCount = m_BitMap[0].GetSize().cx / size.cx;

	m_BitMap[0].Draw(backDC, -size.cx * TitleCountindex, 0, 0);

	if (TitleDeltaTime > 0.05f)
	{
		if (TitleCountindex < TitleCount - 1)
		{
			TitleDeltaTime = 0.0f;
			TitleCountindex++;
		}

	}
}

void Menu::Update(float DeltaTime)
{
}

void Menu::Reset()
{
}
