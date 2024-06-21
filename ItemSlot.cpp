#include "ItemSlot.h"

ItemSlot::ItemSlot()
{
	IvenSlot = NULL;
	item = NULL;
	Selected = false;
	itemType = None;
	pos = { 0,0 };
	ChooseItem = BitMapManager::GetInstance()->GetBitMap(ImageType_Choose_Item);
}

ItemSlot::~ItemSlot()
{
}

void ItemSlot::Draw(HDC backDC, float DeltaTime)
{
	if (item != NULL)
	{
		IvenSlot->Draw(backDC, DeltaTime);
	}
		
	if (Selected) //선택 이미지 그리기
	{
		SIZE size = { 84,71 };
		ChooseItem->AnimationUpdate(backDC, 0, pos.X - 5, pos.Y, size, 1.0f);
	}
}



void ItemSlot::Reset()
{
	IvenSlot->ItemEquipment = false;
	Selected = false;
	itemType = None;
	IvenSlot = NULL;
	item = NULL;
}

void ItemSlot::SlotItemAdd(Item* _item)
{
	IvenSlot = _item;
	item = _item;
}
