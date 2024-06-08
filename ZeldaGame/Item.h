#pragma once
#include "Object.h"

enum EItem
{
	None,
	Item_Sword,	
	Item_Shield,	// 방패
	Item_Lanton,	// 등불
};

enum InGame_Item
{
	InGame_Item_Lanton, // 등불
	InGame_Item_Shield,	//방패
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
	Item(EItem _item, int x, int y, ItemImageType type); //인게임 아이템일시 true
	~Item();
	EItem item; //현재 아이템
	RECT ItemCollision;
	ItemImageType m_type;
	Position itemPos;
	bool InGameItem;
	bool ItemEquipment; // 아이템 장착여부

	virtual void Draw(HDC backDC, float DeltaTime) override;
	void PosUpdate(int x, int y);
	RECT& GetCollision() { return ItemCollision; }
	virtual void Reset() override;
};

