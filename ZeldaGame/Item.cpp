#include "Item.h"

Item::Item(EItem _item)
{
	item = _item;
	itemPos.X = 0;
	itemPos.Y = 0;
	m_BitMap = BitMapManager::GetInstance()->GetBitMap(ImageType_Item);

	
}

Item::~Item()
{
}

void Item::Draw(HDC backDC, float DeltaTime)
{
	m_BitMap[item - 1].Draw(backDC, itemPos.X, itemPos.Y, 0);
}

void Item::PosUpdate(int x, int y)
{
	itemPos.X = x;
	itemPos.Y = y;
}

void Item::Reset()
{
}

