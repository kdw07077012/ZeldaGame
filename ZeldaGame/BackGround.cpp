#include "BackGround.h"

BackGround::BackGround()
{
	m_BitMap = BitMapManager::GetInstance()->GetBitMap(ImageType_BackGround);
	x = 0;
	y = 0;
	m_fMoveDeltaTime = 0.0f;
}

BackGround::~BackGround()
{
}

void BackGround::Draw(HDC backDC, float DeltaTime)
{
	SIZE size = BitMapManager::GetInstance()->GetWindowSize();
	size.cx /= 2;
	size.cy /= 2;

	m_fMoveDeltaTime += DeltaTime;

	if (m_fMoveDeltaTime > 0.05f)
	{
		if (x < 980 - size.cx)
			x = x + (m_fMoveDeltaTime * 200);

		if (y < 620 - size.cy)
			y = y + (m_fMoveDeltaTime * 200);

		m_fMoveDeltaTime = 0.0f;
	}

	m_BitMap[0].BackGroundDraw(backDC, x, y);
}

void BackGround::Update(float DeltaTime)
{
	//980 620
}

void BackGround::Reset()
{
}
