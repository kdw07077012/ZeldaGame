#include "FieldNPC.h"

FieldNPC::FieldNPC()
{ 
	// npc 퀘스트 정의
	ShoeHelp_Quest* quest = new ShoeHelp_Quest;
	current_Quest = quest;
}

FieldNPC::~FieldNPC()
{
}

void FieldNPC::Draw(HDC backDC, float DeltaTime)
{
	SIZE msize = BitMapManager::GetInstance()->GetWindowSize();
	SIZE size = { 25,40 };
	int screenX = (((msize.cx / 2) - (size.cx * 2)) - Camera::GetInstance()->GetX()) + 575;
	int screenY = (((msize.cy / 2) - (size.cy * 2)) - Camera::GetInstance()->GetY()) + 375;

	Collision = { screenX + 10, screenY, screenX + size.cx * 2 - 10, screenY + size.cy * 2 };

	m_BitMap[0].AnimationUpdate(backDC, AnimationCount, screenX, screenY, size, 2.0f);

	if (bCollision)
		m_NpcTextBar[0].CutDraw(backDC, screenX - size.cx, screenY - m_NpcTextBar->GetSize().cy / 2, 0, 0, m_NpcTextBar->GetSize(), 0.5f);
}

bool FieldNPC::EventCollision(RECT player)
{
	RECT temp;

	if (IntersectRect(&temp, &Collision, &player)) // 플레이어 충돌시
	{
		bCollision = true;
		return true;
	}

	bCollision = false;
	return false;
}

void FieldNPC::Update(float DeltaTime)
{
	fMoveDeltaTime += DeltaTime;

	if (fMoveDeltaTime > fAnimSpeed)
	{
		//
		if (AnimationCount + 1 >= MaxAnimCount)
		{
			AnimationCount = 1;
		}
		else
			AnimationCount++;

		fMoveDeltaTime = 0.0f;
	}
}

void FieldNPC::Reset()
{
}
