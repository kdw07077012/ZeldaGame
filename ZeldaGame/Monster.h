#pragma once
#include "Object.h"
#include "math.h"

enum MonsterType
{
	MonsterType_Snake,
	MonsterType_Octoroc,
	MonsterType_Moblin,
};

class Monster : public Object
{
protected:
	 SIZE m_Size; // ���� �ϳ��� ũ��
	 RECT collision;
	 
	 bool Move;		//�̵��ϴ� ��������
	 float m_fAngle;
	 float fSpeed;
public:
	Monster(int x, int y, MonsterType Type);
	~Monster() {};
	virtual void Init(int x, int y) = 0;
	virtual bool Collision(RECT rect) = 0;
	virtual void Draw(HDC backDC, float DeltaTime) override;
	virtual void Hit() = 0;
	virtual void Reset() override;
	RECT& GetCollision() { return collision; }

};

