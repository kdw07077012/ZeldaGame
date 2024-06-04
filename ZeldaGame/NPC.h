#pragma once
#include "Object.h"
#include "Obstacle.h"
class NPC : public Object
{
private:
	BitMap* m_NpcTextBar; // Npc���� �ؽ�Ʈ��
	RECT EventCollision; //�̺�Ʈ �ݸ��� 
public:
	NPC();
	~NPC();
	virtual void Draw(HDC backDC, float DeltaTime) override;
	void Update(float DeltaTime);
	virtual void Reset() override;
};

