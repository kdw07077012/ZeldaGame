#include "OctorocMonster.h"
#include "Camera.h"
#include "GameManager.h"

OctorocMonster::OctorocMonster() : Monster(0, 0, MonsterType_Octoroc)
{
	bulletBitmap = m_BitMap[m_Type];
}

void OctorocMonster::Init(int x, int y)
{
}

void OctorocMonster::Init(int x, int y, int Dir)
{
	m_eDir = Dir;
	m_ix = x;
	m_iy = y;
	fMoveDeltaTime = 0.0f;
	fSpeed = 0.020f;
	HP = OCTOROC_HP;
	Die = false;
	DieAim = false;
	AnimationCount = 0;
	bHit = false;
	BulletPosX = DEFINE_BULLET_POSX;
	Launch = false;
	bulletCollision = { 0,0,0,0 };
	BulletPosY = DEFINE_BULLET_POSY;
	switch (Dir)
	{
	case Octoroc_DOWN:
		m_AttackDir = 0;
		bullet_speed = BULLET_SPEED;
		Bullet_Distance = ATTACK_DISTANCE;
		break;
	case Octoroc_LEFT:
		m_AttackDir = 1;
		bullet_speed = BULLET_SPEED;
		Bullet_Distance = ATTACK_DISTANCE;
		break;
	case Octoroc_RIGHT:
		m_AttackDir = 2;
		bullet_speed = -BULLET_SPEED;
		Bullet_Distance = -ATTACK_DISTANCE;
		break;
	case Octoroc_UP:
		m_AttackDir = 3;
		bullet_speed = -BULLET_SPEED;
		Bullet_Distance = -ATTACK_DISTANCE;
		break;
	default:
		break;
	}
}

void OctorocMonster::Draw(HDC backDC, float DeltaTime)
{
	if (Die)
		return;

	int screenX = (((WINDOWSIZE_WIDTH / 2) - (50)) - Camera::GetInstance()->GetX()) + m_ix;
	int screenY = (((WINDOWSIZE_HEIGHT / 2) - (50)) - Camera::GetInstance()->GetY()) + m_iy;

	collision = { screenX + 10, screenY + 10, screenX + 40 , screenY + 40 };

	if (DieAim)
	{
		m_BitMap[m_Type].AnimationUpdate(backDC, AnimationCount, screenX, screenY, m_Size, 0.5f, 800);
	}
	else
	{
		if (bHit)
			m_BitMap[m_Type].AnimationUpdate(backDC, m_AttackDir, screenX, screenY, m_Size, 0.5f, 1000);
		else
			m_BitMap[m_Type].AnimationUpdate(backDC, Launch ? AnimationCount : 0, screenX, screenY, m_Size, 0.5f, m_eDir);
	}


	switch (m_AttackDir)
	{
	case 1: //왼쪽
	case 2: // 오른쪽
		BulletPosX += DeltaTime * bullet_speed;

		if (m_AttackDir == 0 ? BulletPosX < Bullet_Distance : BulletPosX > Bullet_Distance) // 총알 거리가될때까지 드로우 
		{
			bulletBitmap.AnimationUpdate(backDC, AnimationCount, screenX - BulletPosX, screenY - 10, m_Size, 0.7f, Octoroc_Bullet);
		}
		else
		{
			//LaunchAnim
			BulletPosX = DEFINE_BULLET_POSX; // 총알거리넘어가면 위치 재설정
			Launch = true; // 발사 애니메이션 
		}
		break;
	case 0: // 아래
	case 3: //위쪽
		BulletPosY += DeltaTime * bullet_speed;

		if (m_AttackDir == 0 ? BulletPosY < Bullet_Distance : BulletPosY > Bullet_Distance) // 총알 거리가될때까지 드로우 
		{
			bulletBitmap.AnimationUpdate(backDC, AnimationCount, screenX - 10, (screenY + BulletPosY) - 30, m_Size, 0.7f, Octoroc_Bullet);
		}
		else
		{
			//LaunchAnim
			BulletPosY = DEFINE_BULLET_POSY; // 총알거리넘어가면 위치 재설정
			Launch = true; // 발사 애니메이션 
		}
		break;
	}
	


	bulletCollision = { (screenX + BulletPosX), (screenY + BulletPosY), (screenX + BulletPosX) + 10, (screenY + BulletPosY) + 10};
	

	
	
#ifdef DEBUG
	Rectangle(backDC, bulletCollision.left, bulletCollision.top, bulletCollision.right, bulletCollision.bottom);
	Rectangle(backDC, collision.left, collision.top, collision.right, collision.bottom);
#endif
}


void OctorocMonster::Update(float DeltaTime)
{
	if (Die)
		return;

	if (DieAim)
	{
		fMoveDeltaTime += DeltaTime;

		if (fMoveDeltaTime > 0.04f)
		{
			//
			if (AnimationCount + 1 >= 12)
			{
				Die = true;
			}
			else
				AnimationCount++;

			fMoveDeltaTime = 0.0f;
		}
	}


	fMoveDeltaTime += DeltaTime;

	if (bHit)
	{
		if (fMoveDeltaTime > 0.2f)
		{
			bHit = false;
		}
	}
	else
	{
		if (fMoveDeltaTime > 0.1f)
		{
			//
			if (AnimationCount + 1 >= 2)
			{
				AnimationCount = 0;
				if (Launch) // 총알발사 애니메이션 중인지
					Launch = false;
			}
			else
				AnimationCount++;

			fMoveDeltaTime = 0.0f;
		}
	}


}

bool OctorocMonster::Collision(RECT rect)
{
	if (Die)
		return false;

	RECT tmp;

	if (IntersectRect(&tmp, &bulletCollision, &rect))
	{
		GameManager::GetInstance()->GetPlayer()->DamageHP(0.2F);


		switch (m_AttackDir) // 맞을시 초기위치로 이동
		{
		case 1: //왼쪽
		case 2: // 오른쪽
			BulletPosY = DEFINE_BULLET_POSX; // 총알거리넘어가면 위치 재설정
			Launch = true; // 발사 애니메이션 
			break;
		case 0: // 아래
		case 3: //위쪽
			BulletPosY = DEFINE_BULLET_POSY; // 총알거리넘어가면 위치 재설정
			Launch = true; // 발사 애니메이션 
			break;
		}

		return false;
	}

	return false;
}

void OctorocMonster::Hit()
{
	bHit = true;
	HP -= 20;
	if (HP <= 0)
	{
		DieAim = true;
	}
}

void OctorocMonster::Reset()
{
}
