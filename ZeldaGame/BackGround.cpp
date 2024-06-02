#include "BackGround.h"

BackGround::BackGround(FieldImageType fieldtype)
{

	m_BitMap = BitMapManager::GetInstance()->GetBackGroundBitMap(fieldtype);

	

	tPos = { 0,0 };
	pos = { 0,0 };
	screenPosX = 0;
	screenPosY = 0;
	m_fMoveDeltaTime = 0.0f;
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
