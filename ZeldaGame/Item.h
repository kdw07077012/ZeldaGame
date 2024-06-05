#pragma once
#include "Object.h"

enum EItem
{
	Item_Bow,	    // 활
	Item_Fire,		// 등불
	Item_Shield,	// 방패
	Item_HeartAdd, // 체력추가
	
};


class Item : public Object
{
private:
public:
	Item(EItem _item, int x, int y, bool InGame); //인게임 아이템일시 true
	~Item();
	EItem item; //현재 아이템
	Position itemPos;
	virtual void Draw(HDC backDC, float DeltaTime) override;
	void PosUpdate(int x, int y);

	virtual void Reset() override;
};

