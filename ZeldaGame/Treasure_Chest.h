#pragma once
#include "Object.h"
#include "Coin.h"
#include "Item.h"

#define DROP_ITEM_OFFSET 20

// ����Ʈ ���� �� �������� ����
class Treasure_Chest : public Object
{
private:
	bool ChestDraw; // �������� ǥ��
	RECT collision;
	RECT Event_Collision;
	SIZE size;

	Item* Drop_item;
	Coin* Drop_Coin;
	bool bItem; // 0 : ������ , 1: ����
	bool ItemPickup; // ������ �Ⱦ��ߴ���
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

