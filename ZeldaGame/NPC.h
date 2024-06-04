#pragma once
#include "Object.h"
#include "Obstacle.h"
class NPC : public Object
{
private:
	BitMap* m_NpcTextBar; // Npc들의 텍스트바
	RECT EventCollision; //이벤트 콜리전 
public:
	NPC();
	~NPC();
	virtual void Draw(HDC backDC, float DeltaTime) override;
	void Update(float DeltaTime);
	virtual void Reset() override;
};

