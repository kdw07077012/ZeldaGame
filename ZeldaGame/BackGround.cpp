#include "BackGround.h"

BackGround::BackGround()
{

	
	m_BitMap = BitMapManager::GetInstance()->GetBitMap(ImageType_BackGround);
	pos.X = 0;
	pos.Y = 0;
	m_fMoveDeltaTime = 0.0f;
	Camera::GetInstance()->Init(613, 370); // 613 370
}

BackGround::~BackGround()
{

}

void BackGround::Draw(HDC backDC, float DeltaTime)
{
	m_BitMap[0].BackGroundDraw(backDC, Camera::GetInstance()->GetX(), Camera::GetInstance()->GetY());
}

void BackGround::Update(float DeltaTime)
{

}

void BackGround::Reset()
{
}
