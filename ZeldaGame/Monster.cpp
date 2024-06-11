#include "Monster.h"

Monster::Monster(int x, int y, MonsterType Type) : Object(x,y)
{
	switch (Type)
	{
	case MonsterType_Snake:
		m_BitMap = BitMapManager::GetInstance()->GetBitMap(ImageType_Monster);
		m_Size = { 100,100 };
		break;
	case MonsterType_Octoroc:
		break;
	case MonsterType_Moblin:
		break;
	default:
		break;
	}
	
	collision = { 0,0,0,0 };
	fSpeed = 0.05f;
}

void Monster::Draw(HDC backDC, float DeltaTime)
{

}
void Monster::Reset()
{
}

