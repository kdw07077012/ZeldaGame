#pragma once
#include "Object.h"
#include "BackGround.h"
#include "Player.h"
#include "Camera.h"
#include "Obstacle.h"
#include "FieldNPC.h"
#include <vector>
#include "dstrObj.h"
#include "MiniWood.h"
#include "SnakeMonster.h"
#include "NPC.h"
#include "Treasure_Chest.h"

//#define DEBUG
#define SNAKE_SIZE 4

class Field : public Object
{
protected:
	int obstacleSize;
	int WaterobstacleSize;
	Position EndPosition;
	Position StartPos;
	Obstacle* obstacles;  //�� �ݸ��� 
	Obstacle* Waterobstacles; // �� �ݸ��� 
	Obstacle* NextField_obstacles; // ���� �ʵ�� �� �� �ִ� �ݸ��� 
	BackGround* m_BackGround; // �ʵ� ��� 
	BitMap* MiniWoodBitmap; //�̴Ϻ��� ���� ��Ʈ��

	Treasure_Chest* Chest;
	bool bChestAppears; // �ڽ� ��Ÿ��
	SnakeMonster* m_Snake[SNAKE_SIZE];
	
	MiniWood* wood;
	FieldNPC* m_NPC;
	std::vector<dstrObj*> AttackableObjects;
	bool FieldReset;
public:
	Field();
	~Field();
	virtual void Init();
	virtual void Draw(HDC backDC, float DeltaTime) override;
	void Update(float DeltaTime);
	virtual void Reset() override;
	
	virtual bool Collision(RECT rect);  // �ʵ� �ݸ��� üũ 
	void MiniChangeWood_Collision(RECT rect);
	NPC* FieldNpcCollision(RECT rect);
	void InputCheck(int vKey);
	dstrObj* AttackableObjects_Collision(RECT rect);	//�÷��̾ ���ݰ����� ������Ʈ���� �ݸ���üũ
	void Monsters_Collision(RECT rect);


};

