#pragma once
#include "Object.h"
#include "Obstacle.h"
#include "Camera.h"

class NPC : public Object
{
protected:
	BitMap* m_NpcTextBar; // Npc���� �ؽ�Ʈ��
	bool bCollision; //�ݸ����Ǿ��°�?
	RECT  Collision; //�̺�Ʈ �ݸ��� 
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

