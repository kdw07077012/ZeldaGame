#include "BossMonster.h"
#include "GameManager.h"

#include "math.h"

BossMonster::BossMonster() : Monster(0,0,MonsterType_Boss)
{
	
}

void BossMonster::SceenPosUpdate()
{
	if (boss_State == Boss_State_Die)
	{
		m_ScreenX = (((WINDOWSIZE_WIDTH / 2) - (BossDieAnimSIZE.cx) * 3) - Camera::GetInstance()->GetX()) + m_ix;
		m_ScreenY = (((WINDOWSIZE_HEIGHT / 2) - (BossDieAnimSIZE.cy) * 3) - Camera::GetInstance()->GetY()) + m_iy;
	}
	else
	{
		m_ScreenX = (((WINDOWSIZE_WIDTH / 2) - (m_OneSize.cx)) - Camera::GetInstance()->GetX()) + m_ix;
		m_ScreenY = (((WINDOWSIZE_HEIGHT / 2) - (m_OneSize.cy)) - Camera::GetInstance()->GetY()) + m_iy;
	}

	Sceen_Bulletpos.X = (WINDOWSIZE_WIDTH / 2) - (BulletSize.cx) - Camera::GetInstance()->GetX() + m_ix - m_OneSize.cx / 2;
	Sceen_Bulletpos.Y = (WINDOWSIZE_HEIGHT / 2) - (BulletSize.cy) - Camera::GetInstance()->GetY() + m_iy - m_OneSize.cy / 2;


	Sceen_Raserpos.X = (WINDOWSIZE_WIDTH / 2) - (RaserObjectSIZE.cx * 3) - Camera::GetInstance()->GetX();
	Sceen_Raserpos.Y = (WINDOWSIZE_HEIGHT / 2) - (RaserObjectSIZE.cy * 3) - Camera::GetInstance()->GetY();

	Sceen_RaserBulletpos.X = (WINDOWSIZE_WIDTH / 2) - (RaserBulletSIZE.cx) - Camera::GetInstance()->GetX();
	Sceen_RaserBulletpos.Y = (WINDOWSIZE_HEIGHT / 2) - (RaserBulletSIZE.cy) - Camera::GetInstance()->GetY();
}



void BossMonster::Init(int x, int y)
{
	m_ix = x;
	m_iy = y;
	fMoveDeltaTime = 0.0f;
	fSpeed = 0.020f;
	HP = Boss_MAXHP;
	Die = false;
	DieAim = false;
	AnimationCount = 0;
	boss_State = Boss_State_Idle;
	MaxAnimCount = 0;
	
	BossDieAnimSIZE = { 50,100 };
	BulletSize = { 18,20 };
	RaserObjectSIZE = { 15, 20 };
	RaserBulletSIZE = { 816, 50 };
	Bullet_AnimCount = 0;
	Bullet_AnimMaxCount = 5;
	bBulletPosReset = true; // 총알 위치가 리셋 되었는가

	for (int i = 0; i < 30; i++)
	{
		Boss_Bullet* bullet = new Boss_Bullet;
		bullet->BulletBitmap = m_BitMap[1]; //해당 비트맵의 총알 이미지를 넣어줌
		bullet->pos = { 0,0 };
		bullet->dir = Bullet_Dir((Bullet_LEFT + i));
		bullet->Draw = false;
		bullet->Angle = 0;
		bullets.push_back(bullet);

	}


	for (int i = 0; i < 8; i++)
	{
		Boss_Raser* raser = new Boss_Raser;
		raser->RaserObject = m_BitMap[2];
		raser->BulletBitmap = m_BitMap[3];
		if (i < 4)
		{
			raser->pos = { 0, (50 + (70 *  ( 1 + (i % 4)))) };
			raser->dir = Bullet_RIGHT;
		}
		else
		{
			raser->pos = { 800, (0 + (80 * ( 1 + (i % 4)))) };
			raser->dir = Bullet_LEFT;
		}
		raser->Draw = false;
		raser->Bullet_AnimCount = 0;
		
		Rasers.push_back(raser);
	}

	DelayTime = 0.0f;
	agnle = 0;
	fmoveDeltaTime = 0.0f;
	bRaserAttackCompleate = false;    // 레이저 공격 성공 여부 
	InvisibleAnimMax = 20;  // 사리지는 애니메이션 20 : 사라진 후 대기 지점
	bAttack = true;

}

void BossMonster::SlowRotationAttack(float DeltaTime, bool Random)
{
	static int Count = 0;

	fmoveDeltaTime += DeltaTime;

	if (fmoveDeltaTime > Random ? float(rand() % 1 + 4) * 0.1f : 0.1f) //총알을 한발씩 발사
	{
		if (Count + 1 < bullets.size())
		{
			Count++;
			bullets[Count]->Draw = true;
			if (Random)
				bullets[Count]->Angle = rand() % 360;
		}
		else
		{
			if (BulletsDrawCheck()) //모든총알이 끝났는지 체크
			{
				Count = 0;
				bAttack = true;
				BulletPosReset();
			}
				
		}

		fmoveDeltaTime = 0.0f;
	}



	for (int i = 0; i < bullets.size(); i++) //발사한 총알은 바라보는방향으로 이동
	{
		if (bullets[i]->Draw)
		{
			agnle += DeltaTime * 100;

			if (Random)
			{
				bullets[i]->pos.X += cos((bullets[i]->Angle) * DEG2RAD) * (250 * DeltaTime);
				bullets[i]->pos.Y += sin((bullets[i]->Angle) * DEG2RAD) * (250 * DeltaTime);
			}
			else
			{
				bullets[i]->pos.X += cos((20 * i + 1) * DEG2RAD) * (250 * DeltaTime);
				bullets[i]->pos.Y += sin((20 * i + 1) * DEG2RAD) * (250 * DeltaTime);
				
			}


			// 현위치에서 사정거리 400 일때  그려주지않음
			if (bullets[i]->pos.X > 400 || bullets[i]->pos.X < -400)
			{
				bullets[i]->Draw = false;
			}
			else if (bullets[i]->pos.Y > 400 || bullets[i]->pos.Y < -400)
			{
				bullets[i]->Draw = false;
			}

			
		}
			
	}


	

	
	
}

void BossMonster::everyAngleAttack(float DeltaTime)
{


	for (int i = 0; i < bullets.size(); i++)
	{
		bullets[i]->Draw = true;

		if (bullets[i]->Draw)
		{

			bullets[i]->pos.X += cos(((i + 1) * (360 / bullets.size())) * DEG2RAD) * (200 * DeltaTime);
			bullets[i]->pos.Y += sin(((i + 1) * (360 / bullets.size())) * DEG2RAD) * (200 * DeltaTime);
		}

	}
}

void BossMonster::RaserAttack(HDC backDC, float DeltaTime)
{
	static Bullet_Dir RaserDir = Bullet_RIGHT;

	if (bRaserAttackCompleate)
		return;

	if (AnimationCount > 8)
	{

		for (int i = 0; i < Rasers.size(); i++)
		{

			if (Rasers[i]->dir == RaserDir && Rasers[i]->Bullet_AnimCount < 5)
				Rasers[i]->Draw = true;

			if (Rasers[i]->Draw && Rasers[i]->Bullet_AnimCount <= 5)
			{
				Rasers[i]->RaserObject.AnimationUpdate(backDC, Rasers[i]->dir, Sceen_Raserpos.X + Rasers[i]->pos.X,
					Sceen_Raserpos.Y + Rasers[i]->pos.Y, RaserObjectSIZE, 3.0f, Rasers[i]->Bullet_AnimCount * 20);


				Rasers[i]->BulletBitmap.AnimationUpdate(backDC, 0, (Sceen_RaserBulletpos.X - Raser_OffsetX) + Rasers[i]->pos.X + Rasers[i]->dir * RaserBulletSIZE.cx,
					(Sceen_RaserBulletpos.Y - 5) + Rasers[i]->pos.Y, RaserBulletSIZE, 1.0f, Rasers[i]->Bullet_AnimCount >= 5 ? 50 + (Rasers[i]->dir * 100) : (Rasers[i]->dir * 100));


				if (Rasers[i]->Bullet_AnimCount >= 5)
				{

					Rasers[i]->Collision = { (Sceen_RaserBulletpos.X + Rasers[i]->pos.X) + 20, (Sceen_RaserBulletpos.Y + Rasers[i]->pos.Y) + 20,
						(Sceen_RaserBulletpos.X + Rasers[i]->pos.X) + RaserBulletSIZE.cx * ((Rasers[i]->dir) + 1), 
						(Sceen_RaserBulletpos.Y + Rasers[i]->pos.Y) + RaserBulletSIZE.cy - 20 };

					//Rectangle(backDC, Rasers[i]->Collision.left, Rasers[i]->Collision.top, Rasers[i]->Collision.right, Rasers[i]->Collision.bottom);

					DelayTime += DeltaTime;

					if (DelayTime > 0.5f)
					{
						
						for (auto raser : Rasers)
						{
							raser->Draw = false;
						}
		

						DelayTime = 0.0f;

						if (RaserDir == Bullet_RIGHT)
						{
							RaserDir = Bullet_LEFT;
						}
						else if (RaserDir == Bullet_LEFT)
						{
							// 사라지 지점에서 다시 애니메이션 활성화
							InvisibleAnimMax = InvisibleAnimEnd;
							AnimationCount = 20;
							bRaserAttackCompleate = true;
						}

						
					}

					


				}

			}
		}

	}


}

void BossMonster::BulletPosReset()
{
	for (auto bullet : bullets)
	{
		if (bullet->Draw)
			bullet->Draw = false;

		bullet->pos.X = 0;
		bullet->pos.Y = 0;
	}
}

bool BossMonster::BulletsDrawCheck()
{
	for (auto bullet : bullets)
	{
		if (bullet->Draw)
			return false;
	}

	return true;
	
}

void BossMonster::Draw(HDC backDC, float DeltaTime)
{
	if (Die)
	{	
		return;
	}

	static int random = 0;


	switch (boss_State)
	{
	case Boss_State_Idle:
	case Boss_State_Walk:
	case Boss_State_Attack:
	case Boss_State_Invisible:
		m_BitMap->AnimationUpdate(backDC, bHit ? 3 : AnimationCount, m_ScreenX, m_ScreenY, m_OneSize, 1.0f, m_OneSize.cy * boss_State);
		break;
	case Boss_State_Die:
		m_BitMap[4].AnimationUpdate(backDC, AnimationCount, m_ScreenX - 80, m_ScreenY, BossDieAnimSIZE, 3.0f, 0);
		break;
	default:
		break;
	}
	//보스 캐릭터 그려주는 구문
	
	//everyAngleAttack(DeltaTime);
	

	

	if (boss_State == Boss_State_Idle)
	{
	

		if (!bAttack)
		{
			switch (random)
			{
			case 0:
				SlowRotationAttack(DeltaTime, false); // 기본 공격
				break;
			case 1:
				SlowRotationAttack(DeltaTime, true); // 기본 공격
				break;
			}

		}
		else
		{
			random = rand() % 2;
			bAttack = false;
		}
		

		
	}
	
	
	

	if (boss_State == Boss_State_Attack || boss_State == Boss_State_Idle)
	{

		

		for (auto bullet : bullets) // 총알 구체 그리기
		{

			if (bullet->Draw)
			{
				bullet->BulletBitmap.AnimationUpdate(backDC, Bullet_AnimCount, Sceen_Bulletpos.X + bullet->pos.X,
					Sceen_Bulletpos.Y + bullet->pos.Y, BulletSize, 3.0f, 0);


				bullet->Collision = { (Sceen_Bulletpos.X + bullet->pos.X), (Sceen_Bulletpos.Y + bullet->pos.Y),
			(Sceen_Bulletpos.X + bullet->pos.X) + BulletSize.cx * 3, (Sceen_Bulletpos.Y + bullet->pos.Y) + BulletSize.cy * 3 };

				//Rectangle(backDC, bullet->Collision.left, bullet->Collision.top, bullet->Collision.right, bullet->Collision.bottom);
			}



		}
	}
	else if (boss_State == Boss_State_Invisible)
	{
		if (!bAttack)  // 구체공격 도중 넘어왔다면 활성화된 구체 초기화
		{
			BulletPosReset();
			bAttack = true;
		}

		RaserAttack(backDC, DeltaTime);
	}
	


	
	

	

	collision = { m_ScreenX + Colliison_Offset , m_ScreenY + Colliison_Offset,
		m_ScreenX + (m_OneSize.cx - Colliison_Offset) , m_ScreenY + (m_OneSize.cy - Colliison_Offset)};


	
	//if (DieAim)
	//{
	//	m_BitMap[m_Type].AnimationUpdate(backDC, AnimationCount, screenX, screenY, m_Size, 0.5f, 400);
	//}
	//else
	//{
	//	if (bHit)
	//		m_BitMap[m_Type].AnimationUpdate(backDC, (m_eDir / 100), screenX, screenY, m_Size, 0.5f, 500);
	//	else
	//		m_BitMap->AnimationUpdate(backDC, 0, screenX, screenY, m_Size, 0.5f, 0);
	//}

	//Rectangle(backDC, collision.left, collision.top, collision.right, collision.bottom);
}

void BossMonster::Update(float DeltaTime)
{
	if (Die)
		return;

	SceenPosUpdate();

	fMoveDeltaTime += DeltaTime;

	


	



	if (bHit)
	{
		if (fMoveDeltaTime > 0.1f)
		{
			bHit = false;
			fMoveDeltaTime = 0.0f;
		}
	}
	else
	{

		switch (boss_State)
		{
		case Boss_State_Idle:
			MaxAnimCount = 2;
			break;
		case Boss_State_Walk:
			MaxAnimCount = 6;
		case Boss_State_Attack:
			Bullet_AnimMaxCount = 4;
			break;
		case Boss_State_Invisible:
			MaxAnimCount = InvisibleAnimMax;
			Bullet_AnimMaxCount = 5;
			break;
		case Boss_State_Die:
			MaxAnimCount = 32;
			break;
		default:
			break;
		}


		if (fMoveDeltaTime > 0.05f)
		{


			if (AnimationCount + 1 >= MaxAnimCount)
			{
				if (boss_State == Boss_State_Die)
				{
					Die = true;
				}

				if(boss_State != Boss_State_Invisible)
					AnimationCount = 0;
				else
				{
					if (AnimationCount + 1 >= 28)
					{
						boss_State = Boss_State_Idle;
					}
				}
					
				
			}
			else
				AnimationCount++;


			if (Bullet_AnimCount + 1 >= Bullet_AnimMaxCount)
			{
				Bullet_AnimCount = 0;
			}
			else
				Bullet_AnimCount++;

			fMoveDeltaTime = 0.0f;
		}

		if (boss_State == Boss_State_Invisible)
		{
			RaserDeltaTime += DeltaTime;

			if (RaserDeltaTime > 0.1f)
			{

				for (auto Raser : Rasers) // 레이저 그리기
				{

					if (Raser->Draw)
					{
						if (Raser->Bullet_AnimCount + 1 <= 5)
							Raser->Bullet_AnimCount++;
					}
				}

				RaserDeltaTime = 0.0f;
			}
		}
		
		
	}
}

bool BossMonster::Collision(RECT rect)
{
	RECT tmp;

	for (auto bullet : bullets) // 총알 구체
	{
		if (bullet->Draw)
		{
			if (IntersectRect(&tmp, &bullet->Collision, &rect))
			{
				GameManager::GetInstance()->GetPlayer()->DamageHP(0.2F);
				bullet->Draw = false;
			}
		}
	}

	for (auto Raser : Rasers) // 레이저 그리기
	{

		if (Raser->Draw)
		{
			if (IntersectRect(&tmp, &Raser->Collision, &rect))
			{
				GameManager::GetInstance()->GetPlayer()->DamageHP(1.0f);
			}
		}
	}

    return false;
}

void BossMonster::Hit()
{
	bHit = true;
	HP -= 20;
	if (HP <= 0)
	{
		boss_State = Boss_State_Die;
	}
	else
	{
		if (HP < 120 && bRaserAttackCompleate == false)
		{
			boss_State = Boss_State_Invisible;
		}
	}
}

void BossMonster::Reset()
{
}

void BossMonster::SetState(Boss_State state)
{
	boss_State = state;
	AnimationCount = 0;
}
