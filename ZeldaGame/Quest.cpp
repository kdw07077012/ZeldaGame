#include "Quest.h"

Quest::Quest(QuestType type) : Type(type)
{
	m_BitMap = BitMapManager::GetInstance()->GetBitMap(ImageType_QuestList);
	m_ComplateBitmap = m_BitMap[2];
	size = { 500,80 };
	Complete = false;
	drawDeltaTime = 0.0f;
}

Quest::~Quest()
{

}

void Quest::OnNotify(QuestType type)
{
	
}


void Quest::Draw(HDC backDC, float DeltaTime)
{
	m_BitMap[Type - 1].CutDraw(backDC, 115, 140 + (100 * (Type - 1)), 0, Complete * 80, size, 1.0f);	
}

void Quest::Complate_Draw(HDC backDC, float DeltaTime)
{
	if (CompleteAnim) // 컴플리트 텍스트 띄우기 
	{
		m_ComplateBitmap.Draw(backDC, 50, 400, 1);
		drawDeltaTime += DeltaTime;

		if (drawDeltaTime > 0.5f)
		{
			CompleteAnim = false;
			drawDeltaTime = 0.0f;
		}

	}
		
}


void Quest::Reset()
{					
}
