#include "MiniWood.h"
#include "Camera.h"
MiniWood::MiniWood(int x, int y) : Object(x, y)
{
	m_BitMap = BitMapManager::GetInstance()->GetBitMap(ImageType_MiniWood);
	collision = { 0,0,0,0 };
}

MiniWood::~MiniWood()
{
	
}

void MiniWood::Draw(HDC backDC, float DeltaTime)
{
	SIZE msize = BitMapManager::GetInstance()->GetWindowSize();
	SIZE size = { 38,32 };
	int screenX = (((msize.cx / 2) - (size.cx * 1.5)) - Camera::GetInstance()->GetX()) + m_ix;
	int screenY = (((msize.cy / 2) - (size.cy * 1.5)) - Camera::GetInstance()->GetY()) + m_iy;

	collision = { screenX, screenY, screenX + 57 , screenY + 48 };

	

	m_BitMap->AnimationUpdate(backDC, 0, screenX, screenY, size, 1.5);
}

void MiniWood::Update(float DeltaTime)
{
	
	
}

void MiniWood::Reset()
{
}
