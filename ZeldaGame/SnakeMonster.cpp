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

	


	
	//���� 
	if (!bHit)
	{
		if (GameManager::GetInstance()->GetPlayer()->GetHit()) //�÷��̾ �ǰݹ޾����� ������������
			return;

		float fWidth = GameManager::GetInstance()->GetPlayer()->m_pos.X - m_ix;
		float fHeight = GameManager::GetInstance()->GetPlayer()->m_pos.Y - m_iy;
		float fDiagonal = sqrtf(fWidth * fWidth + fHeight * fHeight); // ��Ŭ��Ʈ �Ÿ� ���

		if (abs(fWidth) < abs(fHeight)) //���Ϸ� �� ����� ���
		{
			if (fHeight <= 0) // ���Ʒ��ִ��� üũ
				m_eDir = 300; // ��
			else
				m_eDir = 0; // �Ʒ�
		}
		else //�¿�� �� ����� ���
		{
			if (fWidth >= 0)
				m_eDir = 100; //����
			else
				m_eDir = 200; // ������
		}

		if (fDiagonal < 150) // �Ÿ��� 300���� �۴ٸ� 
		{
			m_fAngle = acosf(fWidth / fDiagonal);
			if (m_iy < GameManager::GetInstance()->GetPlayer()->m_pos.Y) // �Ƚ��Ͱ� �÷��̾� �Ʒ��� �ִٸ�
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
