#pragma once
#include "Monster.h"
#include <vector>

#define PI 3.141592653589793238462643383279f // ���� ����ϱ� ���� ���� ����
#define DEG2RAD PI / 180 // ������ �������� ��ȯ
#define RAD2DEG 180 / PI // ������ ������ ��ȯ




#define InvisibleAnimEnd 28  // ������� �ִϸ��̼� ����
#define Colliison_Offset 60
#define Raser_OffsetX 20
#define Boss_MAXHP 300
enum Boss_State
{
	Boss_State_Idle,
	Boss_State_Walk,
	Boss_State_Attack,    // ���� : ��üȭ �Ѿ� ����
	Boss_State_Invisible, //��� ����ȭ�� ���� ��ġ�� �̵� ����ȭ �����϶� ������ ����
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



struct Boss_Bullet // ���� ��ü 
{
	Position pos;
	BitMap BulletBitmap; //���� �ǰ� ��ü
	Bullet_Dir dir; // �Ѿ� ����
	bool Draw; //�׸��� �ִ��� üũ
	RECT Collision;
	int Angle;
};

struct Boss_Raser // ���� ������
{
	Position pos;        // ������ ��ġ
	BitMap RaserObject;  // �������� ���� ������Ʈ ��Ʈ��
	BitMap BulletBitmap; //���� ������ ��Ʈ��
	Bullet_Dir dir; // �Ѿ� ����
	bool Draw; //�׸��� �ִ��� üũ
	RECT Collision;
	
	int Bullet_AnimCount;

	
};

class BossMonster : public Monster
{
private:
	Boss_State boss_State; // ���� ����
	std::vector<Boss_Bullet*> bullets; // ��ü�� ����Ʈ
	std::vector< Boss_Raser*> Rasers;  // �������� ���� ����Ʈ
	SIZE BulletSize;  // ��ü �̹���������
	SIZE RaserObjectSIZE; // ������ �� �̹��� ������
	SIZE RaserBulletSIZE; // ������ �̹��� ������
	SIZE BossDieAnimSIZE; //���� �׾����� �̹��� ������
	Position  Sceen_Bulletpos;
	Position  Sceen_Raserpos;
	Position  Sceen_RaserBulletpos;

	int Bullet_AnimCount; // �Ѿ� �ִϸ��̼� ī����
	int Bullet_AnimMaxCount; // �Ѿ� �ִ� �ִϸ��̼� ī����
	bool bBulletPosReset; // 
	float RaserDeltaTime;
	bool bRaserAttackCompleate;
	bool bAttack;
	float DelayTime;
	int InvisibleAnimMax;
	int random;
private:
	void SlowRotationAttack(float DeltaTime, bool Random = false); // ��ü�� 360�������� ������ ����
	void everyAngleAttack(float DeltaTime);   // ��ü���� 0���� 360������ �߻�
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

