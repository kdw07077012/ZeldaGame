#pragma once
#include "Object.h"
#include "Item.h"

#define SLOT_OFFEST_X 110
#define SLOT_OFFEST_Y 78


class ItemSlot : public Object
{
private:
	Item* item; // 해당 슬롯 아이템 
public:
	Item* IvenSlot;     // 슬롯 표시할 인벤아이템
	BitMap* ChooseItem; //아이템 선택 표시 이미지
	Position pos;
	bool Selected; // 선택되었는지
	EItem itemType;

	ItemSlot();
	~ItemSlot();

	Item* GetItem() const {
		if (item != NULL)
			return item;
		return NULL;
	}
	void SlotItemAdd(Item* _item);
	virtual void Draw(HDC backDC, float DeltaTime) override;
	virtual void Reset() override;
};

