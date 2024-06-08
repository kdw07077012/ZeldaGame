#include "dstrObj.h"
#include "Camera.h"
#include <time.h>
dstrObj::dstrObj(dstrObjType Type, int x, int y)
{
	m_type = Type;
	m_ix = x;
	m_iy = y;
	m_BitMap = BitMapManager::GetInstance()->GetBitMap(ImageType_DstrObj);
	collision = { 0,0,0,0 };
	Attacked = false;
	m_coin = new Coin(x, y);
	JarAimTimer = 0.0f;
	switch (m_type)
	{
	case dstrObjType_Thicket:
		m_size = { 19,16 };
		break;
	case dstrObjType_Jar:
		m_size = { 16,16 };
		break;
	default:
		break;
	}
	
	JarAnimCount = 0;


}

dstrObj::~dstrObj()
{
}

void dstrObj::Draw(HDC backDC, float DeltaTime)
{
	SIZE msize = BitMapManager::GetInstance()->GetWindowSize();
	
	int screenX = (((msize.cx / 2) - (m_size.cx * 2)) - (Camera::GetInstance()->GetX()) + m_ix);
	int screenY = (((msize.cy / 2) - (m_size.cy * 2)) - (Camera::GetInstance()->GetY()) + m_iy);

	collision = { screenX, screenY, screenX + m_size.cx * 2 , screenY + m_size.cy * 2 };

	switch (m_type)
	{
	case dstrObjType_Thicket: //덤블 단일애니메이션 
		m_BitMap[m_type].AnimationUpdate(backDC, Attacked, screenX, screenY, m_size, 2.0f);		
		break;
	case dstrObjType_Jar: // 항아리 애니메이션 연속
		m_BitMap[m_type].AnimationUpdate(backDC, JarAnimCount, screenX, screenY, m_size, 2.0f);

		if (Attacked) // 공격받았을시
		{
			// 항아리 파괴 애니메이션 재생
			fAnimDeltaTime += DeltaTime;

			if (JarAnimCount <= 4)
			{
				if (fAnimDeltaTime > 0.01f)
				{
					JarAnimCount++;				
					fAnimDeltaTime = 0.0f;
				}
			}	
		}
		
		break;
	default:
		break;
	}

	if (Attacked && m_CoinProbability)
		m_coin->Draw(backDC, DeltaTime);
	

#ifdef DEBUG
	Rectangle(backDC, collision.left, collision.top, collision.right, collision.bottom);
#endif // DEBUG

}



void dstrObj::Update(float DeltaTime)
{
}

void dstrObj::AttackedObject()
{
	m_CoinProbability = rand() % 2; // 50프로 확률로 드랍
	Attacked = true;
}

void dstrObj::Reset()
{
}
