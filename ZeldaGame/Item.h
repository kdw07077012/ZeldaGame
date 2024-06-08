#pragma once
#include "Object.h"

enum EItem
{
	None,
	Item_Sword,	
	Item_Shield,	// ����
	Item_Lanton,	// ���
};

enum InGame_Item
{
	InGame_Item_Lanton, // ���
	InGame_Item_Shield,	//����
	InGame_Item_HpAdd,
	InGame_Item_Position,

};

enum ItemImageType
{
	ItemImageType_InGame,
	ItemImageType_Inven,
	ItemImageType_HUD,
};


class Item : public Object
{
public:
	Item(EItem _item, int x, int y, ItemImageType type); //�ΰ��� �������Ͻ� true
	~Item();
	EItem item; //���� ������
	RECT ItemCollision;
	ItemImageType m_type;
	Position itemPos;
	bool InGameItem;
	bool ItemEquipment; // ������ ��������

	virtual void Draw(HDC backDC, float DeltaTime) override;
	void PosUpdate(int x, int y);
	RECT& GetCollision() { return ItemCollision; }
	virtual void Reset() override;
};

