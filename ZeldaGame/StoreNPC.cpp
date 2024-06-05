#include "StoreNPC.h"

StoreNPC::StoreNPC()
{
	MaxAnimCount = 17;
	Collisioon.Init(728, 314, 982, 578);
}

StoreNPC::~StoreNPC()
{
}

void StoreNPC::Draw(HDC backDC, float DeltaTime)
{
	SIZE msize = BitMapManager::GetInstance()->GetWindowSize();
	SIZE size = { 25,40 };
	int screenX = (((msize.cx / 2) - (size.cx * 2)) - Camera::GetInstance()->GetX()) + 553;
	int screenY = (((msize.cy / 2) - (size.cy * 2)) - Camera::GetInstance()->GetY()) + 290;

	Collisioon.Draw(backDC, Camera::GetInstance()->GetX(), Camera::GetInstance()->GetY());

	m_BitMap[2].AnimationUpdate(backDC, AnimationCount, screenX, screenY, size, 2.0f);


	if (bCollision)
		m_NpcTextBar[2].CutDraw(backDC, screenX - size.cx, screenY - m_NpcTextBar->GetSize().cy / 2, 0, 0, m_NpcTextBar->GetSize(), 0.5f);
}

bool StoreNPC::EventCollision(RECT player)
{

	RECT temp;

	if (IntersectRect(&temp, &Collisioon.GetCollision(), &player))
	{
		bCollision = true;
		return true;
	}

	bCollision = false;
	return false;
}

void StoreNPC::Update(float DeltaTime)
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

void StoreNPC::Reset()
{
}
