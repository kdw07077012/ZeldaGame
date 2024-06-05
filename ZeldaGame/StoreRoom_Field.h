#pragma once
#include "Field.h"
#include "StoreNPC.h"
#include "Item.h"
#include <vector>
class StoreRoom_Field : public Field
{
private:
	std::vector<Item*> Items;
	StoreNPC* Npc;
public:
	StoreRoom_Field();
	~StoreRoom_Field();
	virtual void Init() override;
	virtual void Draw(HDC backDC, float DeltaTime) override;
	void Update(float DeltaTime);
	virtual void Reset() override;
	virtual bool Collision(RECT rect) override;  // 필드 콜리전 체크 
};

