#pragma once
#include "Object.h"
#include "Obstacle.h"
#include "Camera.h"

class NPC : public Object
{
protected:
	BitMap* m_NpcTextBar; // Npc들의 텍스트바
	bool bCollision; //콜리전되었는가?
	RECT  Collision; //이벤트 콜리전 
	float fMoveDeltaTime;
	float fAnimSpeed;
	int AnimationCount, MaxAnimCount;
public:
	NPC();
	~NPC();
	virtual void Draw(HDC backDC, float DeltaTime) = 0;
	virtual bool EventCollision(RECT player) = 0;
	virtual void Update(float DeltaTime) = 0;
	virtual void Reset() override;
};

