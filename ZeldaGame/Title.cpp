#include "Title.h"

Title::Title()
{
	m_BitMap = BitMapManager::GetInstance()->GetBitMap(ImageType_Title);
}

Title::~Title()
{
}

void Title::PlaySelect()
{
	if (GetAsyncKeyState(VK_RETURN) & 0x8000)
	{
		m_bGameState = true;

	}
}

void Title::Draw(HDC backDC, float DeltaTime)
{
	SIZE size = BitMapManager::GetInstance()->GetWindowSize();
	const int& TitleCount = m_BitMap[0].GetSize().cx / size.cx;
	
	TitleDeltaTime += DeltaTime;

	m_BitMap[0].Draw(backDC, -size.cx * TitleCountindex, 10, 0);

	if (TitleDeltaTime > 0.05f)
	{
		if (TitleCountindex < TitleCount - 1 && !m_bloop)
		{
			TitleDeltaTime = 0.0f;
			TitleCountindex++;

			if (TitleCountindex >= TitleCount - 1)
			{
				m_bloop = true;
				TitleCountindex = TITLE_LOOP;
			}
		}
		else
		{
			if (TitleCountindex < TitleCount - 1)
			{
				TitleDeltaTime = 0.0f;
				TitleCountindex++;
			}
			else
				TitleCountindex = TITLE_LOOP;
		}
	

	}

	
}

void Title::Update(float DeltaTime)
{
	PlaySelect();
}

void Title::Reset()
{
}
