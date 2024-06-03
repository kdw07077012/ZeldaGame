#pragma once
#include "Object.h"
#include "BackGround.h"
#include "Player.h"
#include "Camera.h"
#include "Obstacle.h"

#define DEBUG

class Field : public Object
{
protected:
	int obstacleSize;
	int WaterobstacleSize;
	Obstacle* obstacles;  //�� �ݸ��� 
	Obstacle* Waterobstacles; // �� �ݸ��� 
	Obstacle* NextField_obstacles; // ���� �ʵ�� �� �� �ִ� �ݸ��� 
	BackGround* m_BackGround; // �ʵ� ��� 
public:
	Field();
	~Field();
	virtual void Draw(HDC backDC, float DeltaTime) override;
	void Update(float DeltaTime);
	virtual void Reset() override;
	virtual bool Collision(RECT rect);  // �ʵ� �ݸ��� üũ 



};

