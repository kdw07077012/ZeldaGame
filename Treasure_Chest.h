#pragma once
#include "Object.h"
#include "Coin.h"
#include "Item.h"

#define DROP_ITEM_OFFSET 20

// 퀘스트 성공 및 보물상자 나옴
class Treasure_Chest : public Object
{
private:
	bool ChestDraw; // 보물상자 표시
	RECT collision;
	RECT Event_Collision;
	SIZE size;

	Item* Drop_item;
	Coin* Drop_Coin;
	bool bItem; // 0 : 아이템 , 1: 코인
	bool ItemPickup; // 아이템 픽업했는지
public:
	bool BoxOpen;

	Treasure_Chest(int x, int y);
	~Treasure_Chest();
	virtual void Draw(HDC backDC, float DeltaTime) override;
	void Update(float DeltaTime);
	void Collision();
	virtual void Reset() override;
	RECT& GetCollision() { return collision; }
	RECT& GetEvent_Collision() { return Event_Collision; }

	Coin* GetCoin() { return Drop_Coin; }
};

