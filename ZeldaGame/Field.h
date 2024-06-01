#pragma once
#include "Object.h"
#include "BackGround.h"
#include "Player.h"
#include "Camera.h"
#include "Obstacle.h"

//#define DEBUG

class Field : public Object
{
public:
	Field();
	~Field();
	virtual void Draw(HDC backDC, float DeltaTime) override;
	void Update(float DeltaTime);
	virtual void Reset() override;
	bool Collision(RECT rect);
	int obstacleSize;
	int WaterobstacleSize;
	Obstacle *obstacles;
	Obstacle *Waterobstacles;
};

