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

