#pragma once
#include "Monster.h"

#define SANKE_HP 50

class SnakeMonster : public Monster
{
private:
	float fMoveDeltaTime;
	int AnimationCount;
	bool bHit;
	bool Tracking; //추적중인가
	int  m_eDir;
	int  HP;
	bool DieAim;
	bool Die;
public:
	SnakeMonster() : Monster(0,0,MonsterType_Snake) {
		Move = true;
	};
	~SnakeMonster() {};

	virtual void Init(int x, int y) override;
	virtual void Draw(HDC backDC, float DeltaTime) override;
	void Update(float DeltaTime);
	virtual bool Collision(RECT rect) override;
	virtual void Hit() override;
	virtual void Reset() override;
};

