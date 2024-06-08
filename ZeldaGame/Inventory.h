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
	BitMap* Choose_Item; //���þ����� ǥ��
	ItemSlot* SelectItem; //���缱������ ����
	Inventory();
	~Inventory();
	virtual void Draw(HDC backDC, float DeltaTime) override;
	void Update(float DeltaTime, POINT mousePos);
	bool AddItem(Item* _item);
	bool Enabled; //�̺��丮�� �����ִ���

	virtual void Reset() override;
};

