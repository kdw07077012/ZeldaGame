#include "SnakeMonster.h"
#include "Camera.h"
#include "GameManager.h"
SnakeMonster::SnakeMonster() : Monster(0, 0, MonsterType_Snake)
{
}
void SnakeMonster::Init(int x, int y)
{
	m_ix = x;
	m_iy = y;
	fMoveDeltaTime = 0.0f;
	fSpeed = 0.020f;
	HP = SANKE_HP;
	Die = false;
	DieAim = false;
	AnimationCount = 0;
	MaxAnimCount = 4;
}
void SnakeMonster::Draw(HDC backDC, float DeltaTime)
{
	if (Die)
		return;

	int screenX = (((WINDOWSIZE_WIDTH / 2) - (50)) - Camera::GetInstance()->GetX()) + m_ix;
	int screenY = (((WINDOWSIZE_HEIGHT / 2) - (50)) - Camera::GetInstance()->GetY()) + m_iy;

	collision = { screenX + 20, screenY + 10, screenX + 50 , screenY + 40 };

	if (DieAim)
	{
		m_BitMap[m_Type].AnimationUpdate(backDC, AnimationCount, screenX, screenY, m_OneSize, 0.5f, 400);
	}
	else
	{
		if (bHit)
			m_BitMap[m_Type].AnimationUpdate(backDC, (m_eDir / 100), screenX, screenY, m_OneSize, 0.5f, 500);
		else
			m_BitMap[m_Type].AnimationUpdate(backDC, Tracking ? AnimationCount : 0, screenX, screenY, m_OneSize, 0.5f, m_eDir);
	}

	//Rectangle(backDC, collision.left, collision.top, collision.right, collision.bottom);
}

void SnakeMonster::Update(float DeltaTime)
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
		if (fMoveDeltaTime > 0.1f)
		{
			bHit = false;
		}
	}
	else
	{
		if (fMoveDeltaTime > 0.04f)
		{
			//
			if (AnimationCount + 1 >= MaxAnimCount)
			{
				AnimationCount = 0;
			}
			else
				AnimationCount++;

			fMoveDeltaTime = 0.0f;
		}
	}

	


	
	//추적 
	if (!bHit)
	{
		if (GameManager::GetInstance()->GetPlayer()->GetHit()) //플레이어가 피격받았으면 추적하지않음
			return;

		float fWidth = GameManager::GetInstance()->GetPlayer()->m_pos.X - m_ix;
		float fHeight = GameManager::GetInstance()->GetPlayer()->m_pos.Y - m_iy;
		float fDiagonal = sqrtf(fWidth * fWidth + fHeight * fHeight); // 유클리트 거리 계산

		if (abs(fWidth) < abs(fHeight)) //상하로 더 가까운 경우
		{
			if (fHeight <= 0) // 위아래있는지 체크
				m_eDir = 300; // 위
			else
				m_eDir = 0; // 아래
		}
		else //좌우로 더 가까운 경우
		{
			if (fWidth >= 0)
				m_eDir = 100; //왼쪽
			else
				m_eDir = 200; // 오른쪽
		}

		if (fDiagonal < 150) // 거리가 300보다 작다면 
		{
			m_fAngle = acosf(fWidth / fDiagonal);
			if (m_iy < GameManager::GetInstance()->GetPlayer()->m_pos.Y) // 믄스터가 플레이어 아래에 있다면
				m_fAngle *= -1;

			Tracking = true;
			m_ix += fDiagonal * cos(m_fAngle) * fSpeed;
			m_iy -= fDiagonal * sin(m_fAngle) * fSpeed;

		}
		else
			Tracking = false;

	}

	
	





	
	

	
}

bool SnakeMonster::Collision(RECT rect)
{
	if (Die)
		return false;

	RECT tmp;

	if (IntersectRect(&tmp, &collision, &rect))
	{
		GameManager::GetInstance()->GetPlayer()->DamageHP(0.2F);
		return false;
	}


	return false;
}

void SnakeMonster::Hit()
{
	bHit = true;
	HP -= 20;
	if (HP <= 0)
	{
		DieAim = true;
		GameManager::GetInstance()->Quest_OnNotify(QuestType_SnakeSkill);
	}
}

void SnakeMonster::Reset()
{

}
