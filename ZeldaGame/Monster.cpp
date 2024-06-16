#include "Monster.h"

Monster::Monster(int x, int y, MonsterType _Type) : Object(x,y)
{
	m_BitMap = BitMapManager::GetInstance()->GetBitMap(ImageType_Monster);
	m_Size = { 100,100 };
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

