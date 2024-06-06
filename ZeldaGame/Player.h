#pragma once
#include "Object.h"
#include "Camera.h"

#define PLAYER_MAX_SPEED 300

enum PlayerState
{
	PlayerState_IDLE,		// ������ �ִ»���
	PlayerState_WALK,     //�ȴ»���
	PlayerState_FALLWATER, // ���� ��������
	PlayerState_Attack,
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
	BitMap* m_playerSkillDirBitmap[4];

	PlayerState m_playerState; //�÷��̾� ����
	RECT player_rect;			// �ݸ���
	SIZE size;
	Direction dir;
	
	SIZE msize;

	bool Skill;
	bool AnimLoop;
	bool bHit;
	float DieDeltaTime;
	int MaxAnimCount;
	bool m_bmoveable;
	int AnimationCount;
	float fMoveDeltaTime;
	float fAnimSpeed;
	int screenPosX;
	int screenPosY;
	int CoinCount;
public:
	Player();
	~Player();

	Position m_pos;
	void AddCoin(int Count);
	void AttackCheck();
	bool PlayerInput(float DeltaTime);
	virtual void Draw(HDC backDC, float DeltaTime) override;
	void Update(float DeltaTime);
	virtual void Reset() override;
	int GetCurrentCoin()const { return CoinCount; }
	

	void SetPlayerState(PlayerState state);
	Position GetPlayerPos() const { return m_pos; }
	

};

