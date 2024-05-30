#pragma once
#include "Object.h"
#include "BackGround.h"
#include "Player.h"
#include "Camera.h"

class Field : public Object
{
public:
	Field();
	~Field();
	virtual void Draw(HDC backDC, float DeltaTime) override;
	void Update(float DeltaTime);
	virtual void Reset() override;
	bool Collision(RECT rect);
	RECT test_rect;
};

