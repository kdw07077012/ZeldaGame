#include "Item.h"
#include "Camera.h"
Item::Item(EItem _item, int x, int y, bool InGame)
{
	item = _item;
	itemPos.X = x;
	itemPos.Y = y;
	if(InGame)
		m_BitMap = BitMapManager::GetInstance()->GetBitMap(ImageType_Item);
	else
		m_BitMap = BitMapManager::GetInstance()->GetBitMap(ImageType_InvenItem);
	
	
	
}

Item::~Item()
{
}

void Item::Draw(HDC backDC, float DeltaTime)
{
	SIZE msize = BitMapManager::GetInstance()->GetWindowSize();
	SIZE size = { 14,16 };
	int screenX = (((msize.cx / 2) - (size.cx)) - (Camera::GetInstance()->GetX()) + itemPos.X);
	int screenY = (((msize.cy / 2) - (size.cy * 4)) - (Camera::GetInstance()->GetY()) + itemPos.Y);
	
	m_BitMap[item].AnimationUpdate(backDC, 0, screenX, screenY, size, 2.0f);
}

void Item::PosUpdate(int x, int y)
{

}

void Item::Reset()
{
}

