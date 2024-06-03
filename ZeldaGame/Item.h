#pragma once
#include "Object.h"

enum EItem
{
	None,
	Item_Bow,	    // 활
	Item_Fire,		// 등불
	Item_Shield,	// 방패
	Item_Boomerang, // 부메랑
	
};


class Item : public Object
{

public:
	Item(EItem _item);
	~Item();
	EItem item; //현재 아이템
	Position itemPos;
	virtual void Draw(HDC backDC, float DeltaTime) override;
	void PosUpdate(int x, int y);

	virtual void Reset() override;
};

