#include "Monster.h"

Monster::Monster(int x, int y, MonsterType _Type) : Object(x,y)
{
	if (_Type == MonsterType_Boss)
	{
		m_BitMap = BitMapManager::GetInstance()->GetBitMap(ImageType_Boss);
		m_OneSize = { 300,300 };
	}
	else
	{
		m_BitMap = BitMapManager::GetInstance()->GetBitMap(ImageType_Monster);
		m_OneSize = { 100,100 };
	}
	
	
	m_Type = _Type;
	collision = { 0,0,0,0 };
	fSpeed = 0.05f;
}

void Monster::Draw(HDC backDC, float DeltaTime)
{

}
void Monster::Reset()
{
}

