#pragma once
#include "Object.h"
#include "Camera.h"

#define PLAYER_MAX_SPEED 300

enum PlayerState
{
	PlayerState_IDLE,		// 가만히 있는상태
	PlayerState_WALK,     //걷는상태
	PlayerState_FALLWATER, // 물에 빠진상태
	PlayerState_HIT,	   // 히트
	PlayerState_PICKUP,   //물건줍는 상태
	PlayerState_PICKUP_WALK, //물건줍은상태에서 걷는 상태
	PlayerState_PULL,		//물건 당기는 상태
	PlayerState_ROLL,	  //구르는상태
};

enum Direction
{
	LEFT,
	RIGHT,
	UP,
	DOWN,
};

class Player : public Object
{
private:
	PlayerDirBitmap m_playerDirBitmap;
	
public:
	Player();
	~Player();
	
	RECT player_rect;
	SIZE size;
	int MaxAnimCount;
	Direction dir;
	bool m_bmoveable;
	Position m_pos;
	int AnimationCount;
	float fMoveDeltaTime;
	void PlayerInput(float DeltaTime);
	virtual void Draw(HDC backDC, float DeltaTime) override;
	void Update(float DeltaTime);
	virtual void Reset() override;
	int screenPosX;
	int screenPosY;
	SIZE msize;

	Position GetPlayerPos() const { return m_pos; }
	

};

