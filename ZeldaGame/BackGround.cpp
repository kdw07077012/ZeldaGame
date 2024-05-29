#include "BackGround.h"

BackGround::BackGround()
{

	
	m_BitMap = BitMapManager::GetInstance()->GetBitMap(ImageType_BackGround);
	pos.X = 0;
	pos.Y = 0;
	m_fMoveDeltaTime = 0.0f;
	Camera::GetInstance()->Init(100, 100);
}

BackGround::~BackGround()
{
}

void BackGround::Draw(HDC backDC, float DeltaTime)
{
	int screenPosX =  pos.X + Camera::GetInstance()->GetX();
	int screenPosY =  pos.Y + Camera::GetInstance()->GetY();
	
	//m_fMoveDeltaTime += DeltaTime;
	//
	//if (m_fMoveDeltaTime > 0.05f)
	//{
	//	m_fMoveDeltaTime = 0.0f;
	//}

	m_BitMap[0].BackGroundDraw(backDC, screenPosX, screenPosY);

}

void BackGround::Update(float DeltaTime)
{

}

void BackGround::Reset()
{
}
