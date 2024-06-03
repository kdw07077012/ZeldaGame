#include "HUD.h"

HUD::HUD()
{
	m_BitMap = BitMapManager::GetInstance()->GetBitMap(ImageType_HUD);
}

HUD::~HUD()
{
}

void HUD::Draw(HDC backDC, float DeltaTime)
{
	m_BitMap->Draw(backDC, 0, 0, 1);
}

void HUD::Update(float DeltaTime)
{
}

void HUD::Reset()
{
}
