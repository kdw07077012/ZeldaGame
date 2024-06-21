#pragma once
#include "NPC.h"
class ShoeNPC : public NPC
{
private:
	Obstacle Collisioon;
public:
	ShoeNPC();
	~ShoeNPC();
	virtual void Draw(HDC backDC, float DeltaTime) override;
	virtual bool EventCollision(RECT player) override;
	virtual void Update(float DeltaTime) override;
	virtual void Reset() override;
};

