#pragma once
#include "Object.h"
#include "Camera.h"
#include "Item.h"
#define PLAYER_MAX_SPEED 300

enum PlayerState
{
	PlayerState_IDLE,		// 가만히 있는상태
	PlayerState_WALK,     //걷는상태
	PlayerState_FALLWATER, // 물에 빠진상태
	PlayerState_Attack,
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
	BitMap *m_playerDirBitmap[4];
	BitMap* m_playerSkillDirBitmap[4];

	PlayerState m_playerState; //플레이어 상태
	RECT player_rect;			// 콜리전
	SIZE size;
	Direction dir;
	
	SIZE msize;
	EItem Equipment[2]; // 현재 장비 0 : 무기 1: 장비

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

