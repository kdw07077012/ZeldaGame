#include "Item.h"
#include "Camera.h"
Item::Item(EItem _item, int x, int y, ItemImageType type)
{
	item = _item;
	itemPos.X = x;
	itemPos.Y = y;

	switch (type)
	{
	case ItemImageType_InGame:
		m_BitMap = BitMapManager::GetInstance()->GetBitMap(ImageType_Item);
		break;
	case ItemImageType_Inven:
	case ItemImageType_HUD:
		m_BitMap = BitMapManager::GetInstance()->GetBitMap(ImageType_InvenItem);
		break;
	default:
		break;
	}
		
	m_type = type;
	ItemEquipment = false;
	
}

Item::~Item()
{
}

void Item::Draw(HDC backDC, float DeltaTime)
{
	SIZE msize = BitMapManager::GetInstance()->GetWindowSize();

	SIZE size;
	int screenX = 0;
	int screenY = 0;

	if (m_type == ItemImageType_InGame)
	{
		size = { 14,16 };
		screenX = (((msize.cx / 2) - (size.cx)) - (Camera::GetInstance()->GetX()) + itemPos.X);
		screenY = (((msize.cy / 2) - (size.cy * 4)) - (Camera::GetInstance()->GetY()) + itemPos.Y);

		ItemCollision = { screenX, screenY, screenX + size.cx * 2 , screenY + size.cy * 4 };
		Rectangle(backDC, ItemCollision.left, ItemCollision.top, ItemCollision.right, ItemCollision.bottom);
		m_BitMap[item].AnimationUpdate(backDC, 0, screenX, screenY, size, 2.0f);

		
	}

	if (item == None)
		return;

	switch (m_type)
	{
	case ItemImageType_Inven:
		size = {  84,71 };

		if (ItemEquipment)
		{
			if (item != Item_Sword)
				m_BitMap[item - 1].AnimationUpdate(backDC, 2, itemPos.X - 5, itemPos.Y, size, 1.0f);
			else
				m_BitMap[item - 1].AnimationUpdate(backDC, 1, itemPos.X - 5, itemPos.Y, size, 1.0f);
		
		}
		else
			m_BitMap[item - 1].AnimationUpdate(backDC, 0, itemPos.X - 5, itemPos.Y, size, 1.0f);
		break;
	case ItemImageType_HUD:
		size = { 53,42 };
		m_BitMap[item + 2].AnimationUpdate(backDC, 0, itemPos.X, itemPos.Y, size, 1.0f);
		break;
	default:
		break;
	}

	
}

void Item::PosUpdate(int x, int y)
{

}

void Item::Reset()
{
}

