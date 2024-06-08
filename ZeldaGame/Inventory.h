#pragma once
#include "Object.h"
#include "Item.h"
#include <vector>
#include "ItemSlot.h"

#define SLOT_STARTX 157
#define SLOT_STARTY 120

#define SLOT_SIZEX 80
#define SLOT_SIZEY 65

#define SLOT_COUNT 12


class Inventory : public Object
{
public:
	std::vector<ItemSlot*> itemSlots;
	Position SlotPos[SLOT_COUNT];
	BitMap* Choose_Item; //선택아이템 표시
	ItemSlot* SelectItem; //현재선택중인 슬롯
	Inventory();
	~Inventory();
	virtual void Draw(HDC backDC, float DeltaTime) override;
	void Update(float DeltaTime, POINT mousePos);
	bool AddItem(Item* _item);
	bool Enabled; //이벤토리가 켜져있는지

	virtual void Reset() override;
};

