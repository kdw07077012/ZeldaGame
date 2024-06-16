#pragma once
#include "Monster.h"
#define OCTOROC_HP 50

#define Octoroc_DOWN 0
#define Octoroc_LEFT 300 
#define Octoroc_RIGHT 500 
#define Octoroc_UP 700 

#define Octoroc_Bullet 900
#define ATTACK_DISTANCE 300
#define DEFINE_BULLET_POSX 20
#define DEFINE_BULLET_POSY 20
#define BULLET_SPEED 250

class OctorocMonster : public Monster
{
private:
	BitMap bulletBitmap;
	RECT bulletCollision;
	int BulletPosX;
	int BulletPosY;
	int bullet_speed;
	int Bullet_Distance;
	bool Launch;
	int m_AttackDir;
public:
	OctorocMonster(); // 옥토퍼스 보는방향 정하기 
	~OctorocMonster() {};

	virtual void Init(int x, int y) override;
	void Init(int x, int y, int dir);
	virtual void Draw(HDC backDC, float DeltaTime) override;
	void Update(float DeltaTime);
	virtual bool Collision(RECT rect) override;
	virtual void Hit() override;
	virtual void Reset() override;
};

