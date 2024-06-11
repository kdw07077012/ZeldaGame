#pragma once
#include "Field.h"
#include "StoreNPC.h"
#include "Item.h"
#include <vector>
#include "Obstacle.h"
class StoreRoom_Field : public Field
{
private:
	std::vector<Item*> Items;
	bool itembarDraw;
	int itembarCount;
	StoreNPC* Npc;
	int ItemPrice[4];
	BitMap* TextBarBitMap; //������ ��ȣ�ۿ� �ؽ�Ʈ��
public:
	StoreRoom_Field();
	~StoreRoom_Field();
	virtual void Init() override;
	virtual void Draw(HDC backDC, float DeltaTime) override;
	void Update(float DeltaTime);
	void Buy_InputCheck();
	virtual void Reset() override;
	virtual bool Collision(RECT rect) override;  // �ʵ� �ݸ��� üũ 
};

