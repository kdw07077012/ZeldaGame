#pragma once
#include "NPC.h"
class FieldNPC : public NPC
{
public:
	FieldNPC();
	~FieldNPC();
	virtual void Draw(HDC backDC, float DeltaTime) override;
	virtual bool EventCollision(RECT player) override;
	virtual void Update(float DeltaTime) override;
	virtual void Reset() override;
};

