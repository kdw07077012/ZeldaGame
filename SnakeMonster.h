#pragma once
#include "Monster.h"

#define SANKE_HP 50

class SnakeMonster : public Monster
{
private:
	bool Tracking; //추적중인가
public:
	SnakeMonster();
	~SnakeMonster() {};

	virtual void Init(int x, int y) override;
	virtual void Draw(HDC backDC, float DeltaTime) override;
	void Update(float DeltaTime);
	virtual bool Collision(RECT rect) override;
	virtual void Hit() override;
	virtual void Reset() override;
};

