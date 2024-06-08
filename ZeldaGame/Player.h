#pragma once
#include "Object.h"
#include "Camera.h"
#include "Item.h"
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
	EItem Equipment[2]; // ���� ��� 0 : ���� 1: ���

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
	
	float PlayerHP;
	int PlayerMaxHP;
	
public:
	Player();
	~Player();

	Position m_pos;
	void AddCoin(int Count);
	void RemvoeCoin(int Count);
	void AttackCheck();
	bool PlayerInput(float DeltaTime);
	virtual void Draw(HDC backDC, float DeltaTime) override;
	void Update(float DeltaTime);
	void EqupmentAdd(EItem item, bool Equipped);
	virtual void Reset() override;
	int GetCurrentCoin()const { return CoinCount; }
	float GetHp() const { return PlayerHP; }
	float GetMaxHP() const { return PlayerMaxHP; }

	void DamageHP(float dmage) { PlayerHP -= dmage; }
	void AddMaxHP() { PlayerMaxHP += 1; }
	void Hp_Portion();
	void SetPlayerState(PlayerState state);
	Position GetPlayerPos() const { return m_pos; }
	

};

