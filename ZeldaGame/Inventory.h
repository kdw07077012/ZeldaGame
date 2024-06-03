#pragma once
#include "Object.h"
#include "Item.h"
#include <vector>

#define SLOT_STARTX 157
#define SLOT_STARTY 120

#define SLOT_SIZEX 80
#define SLOT_SIZEY 65

#define SLOT_COUNT 12

struct ItemSlot
{
	Position pos;
	bool Selected = false; // 선택되었는지
	Item* item; // 해당 슬롯 아이템 
};

class Inventory : public Object
{
public:
	std::vector<ItemSlot*> itemSlots;
	Position SlotPos[SLOT_COUNT];
	
	Inventory();
	~Inventory();
	virtual void Draw(HDC backDC, float DeltaTime) override;
	void Update(float DeltaTime, POINT mousePos);
	bool AddItem(Item* _item);
	bool Enabled; //이벤토리가 켜져있는지

	virtual void Reset() override;
};

