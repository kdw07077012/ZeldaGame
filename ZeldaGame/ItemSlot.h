#pragma once
#include "Object.h"
#include "Item.h"

#define SLOT_OFFEST_X 110
#define SLOT_OFFEST_Y 78


class ItemSlot : public Object
{
private:
	Item* item; // �ش� ���� ������ 
public:
	Item* IvenSlot;     // ���� ǥ���� �κ�������
	BitMap* ChooseItem; //������ ���� ǥ�� �̹���
	Position pos;
	bool Selected; // ���õǾ�����
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

