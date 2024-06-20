#pragma once
#include "Monster.h"
#include <vector>

#define PI 3.141592653589793238462643383279f // 원을 사용하기 위해 파이 정의
#define DEG2RAD PI / 180 // 각도를 라디안으로 변환
#define RAD2DEG 180 / PI // 라디안을 각도로 변환




#define InvisibleAnimEnd 28  // 사라지는 애니메이션 길이
#define Colliison_Offset 60
#define Raser_OffsetX 20
#define Boss_MAXHP 300
enum Boss_State
{
	Boss_State_Idle,
	Boss_State_Walk,
	Boss_State_Attack,    // 공격 : 구체화 총알 공격
	Boss_State_Invisible, //잠시 투명화후 랜덤 위치로 이동 투명화 상태일때 레이저 공격
	Boss_State_Die,
};

enum Bullet_Dir
{
	Bullet_LEFT,
	Bullet_RIGHT,
	Bullet_UP,
	Bullet_DOWN,
	Bullet_L_UP,
	Bullet_L_DOWN,
	Bullet_R_UP,
	Bullet_R_DOWN,
};



struct Boss_Bullet // 보스 구체 
{
	Position pos;
	BitMap BulletBitmap; //보스 피격 구체
	Bullet_Dir dir; // 총알 방향
	bool Draw; //그리고 있는지 체크
	RECT Collision;
	int Angle;
};

struct Boss_Raser // 보스 레이저
{
	Position pos;        // 레이저 위치
	BitMap RaserObject;  // 레이저가 나갈 오브젝트 비트맵
	BitMap BulletBitmap; //보스 레이저 비트맵
	Bullet_Dir dir; // 총알 방향
	bool Draw; //그리고 있는지 체크
	RECT Collision;
	
	int Bullet_AnimCount;

	
};

class BossMonster : public Monster
{
private:
	Boss_State boss_State; // 보스 상태
	std::vector<Boss_Bullet*> bullets; // 구체를 리스트
	std::vector< Boss_Raser*> Rasers;  // 레이저를 담을 리스트
	SIZE BulletSize;  // 구체 이미지사이즈
	SIZE RaserObjectSIZE; // 레이저 눈 이미지 사이즈
	SIZE RaserBulletSIZE; // 레이저 이미지 사이즈
	SIZE BossDieAnimSIZE; //보스 죽었을때 이미지 사이즈
	Position  Sceen_Bulletpos;
	Position  Sceen_Raserpos;
	Position  Sceen_RaserBulletpos;

	int Bullet_AnimCount; // 총알 애니메이션 카운터
	int Bullet_AnimMaxCount; // 총알 최대 애니메이션 카운터
	bool bBulletPosReset; // 
	float RaserDeltaTime;
	bool bRaserAttackCompleate;
	bool bAttack;
	float DelayTime;
	int InvisibleAnimMax;
	int random;
private:
	void SlowRotationAttack(float DeltaTime, bool Random = false); // 구체들 360각도에서 나가는 공격
	void everyAngleAttack(float DeltaTime);   // 구체들이 0부터 360각도에 발사
	void RaserAttack(HDC backDC, float DeltaTime);
	void BulletPosReset();
	bool BulletsDrawCheck();
	float agnle;
	float fmoveDeltaTime;
public:
	BossMonster();
	~BossMonster() {};

	void SceenPosUpdate();
	virtual void Init(int x, int y) override;
	virtual void Draw(HDC backDC, float DeltaTime) override;
	void Update(float DeltaTime);
	virtual bool Collision(RECT rect) override;
	virtual void Hit() override;
	virtual void Reset() override;
	void SetState(Boss_State state);
};

