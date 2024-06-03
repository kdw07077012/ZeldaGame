#pragma once
#include "Object.h"
#include "Camera.h"

#define PLAYER_MAX_SPEED 300

enum PlayerState
{
	PlayerState_IDLE,		// ������ �ִ»���
	PlayerState_WALK,     //�ȴ»���
	PlayerState_FALLWATER, // ���� ��������
	PlayerState_HIT,	   // ��Ʈ
	PlayerState_PICKUP,   //�����ݴ� ����
	PlayerState_PICKUP_WALK, //�����������¿��� �ȴ� ����
	PlayerState_PULL,		//���� ���� ����
	PlayerState_ROLL,	  //�����»���
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
	BitMap *m_playerDirBitmap[4];
	
public:
	Player();
	~Player();
	
	bool AnimLoop;
	bool bHit;
	float DieDeltaTime;
	PlayerState m_playerState;
	RECT player_rect;
	SIZE size;
	int MaxAnimCount;
	Direction dir;
	bool m_bmoveable;
	Position m_pos;
	int AnimationCount;
	float fMoveDeltaTime;
	float fAnimSpeed;
	bool PlayerInput(float DeltaTime);
	virtual void Draw(HDC backDC, float DeltaTime) override;
	void Update(float DeltaTime);
	virtual void Reset() override;
	int screenPosX;
	int screenPosY;
	SIZE msize;

	void SetPlayerState(PlayerState state);
	Position GetPlayerPos() const { return m_pos; }
	

};

