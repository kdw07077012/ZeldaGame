#pragma once
#include "Object.h"
#include "BackGround.h"
#include "Player.h"
#include "Camera.h"
#include "Obstacle.h"

//#define DEBUG

class Field : public Object
{
protected:
	int obstacleSize;
	int WaterobstacleSize;
	Position EndPosition;
	Obstacle* obstacles;  //벽 콜리전 
	Obstacle* Waterobstacles; // 물 콜리전 
	Obstacle* NextField_obstacles; // 다음 필드로 갈 수 있는 콜리전 
	BackGround* m_BackGround; // 필드 배경 
public:
	Field();
	~Field();
	virtual void Init();
	virtual void Draw(HDC backDC, float DeltaTime) override;
	void Update(float DeltaTime);
	virtual void Reset() override;
	virtual bool Collision(RECT rect);  // 필드 콜리전 체크 



};

