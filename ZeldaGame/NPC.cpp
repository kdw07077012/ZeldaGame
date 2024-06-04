#include "NPC.h"
#include "Camera.h"
NPC::NPC()
{
	m_BitMap = BitMapManager::GetInstance()->GetBitMap(ImageType_NPC);
	m_NpcTextBar = BitMapManager::GetInstance()->GetBitMap(ImageType_NPCTextBar);

	
}

NPC::~NPC()
{
}

void NPC::Draw(HDC backDC, float DeltaTime)
{
	SIZE msize = BitMapManager::GetInstance()->GetWindowSize();
	SIZE size = { 25,40 };
	int screenX = (((msize.cx / 2) - (size.cx * 2)) - Camera::GetInstance()->GetX()) + 550;
	int screenY = (((msize.cy / 2) - (size.cy * 2)) - Camera::GetInstance()->GetY()) + 365;
	
	EventCollision = { screenX + 10, screenY, screenX + size.cx * 2 - 10, screenY + size.cy * 2 };
	
	m_BitMap->AnimationUpdate(backDC,1, screenX, screenY, size, 2.0f);
	m_NpcTextBar->CutDraw(backDC, screenX - size.cx, screenY - m_NpcTextBar->GetSize().cy / 2, 0 , 0 , m_NpcTextBar->GetSize(), 0.5f);
}

void NPC::Update(float DeltaTime)
{
	RECT temp;

	//if (IntersectRect(&tmp, &NextField_obstacles[1].GetCollision(), &rect))
}

void NPC::Reset()
{
}
