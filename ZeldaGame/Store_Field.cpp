#include "Store_Field.h"

Store_Field::Store_Field()
{
	m_bShoeStroe = new BackGround(FieldType_Store_ShoeStroe);
	m_bShoeStroe = new BackGround(FieldType_Store_StoreRoom);
	m_BackGround = new BackGround(FieldType_Store);
}

Store_Field::~Store_Field()
{
}

void Store_Field::Draw(HDC backDC, float DeltaTime)
{
	m_BackGround->Draw(backDC, DeltaTime);
}

void Store_Field::Update(float DeltaTime)
{
}

void Store_Field::Reset()
{
}

bool Store_Field::Collision(RECT rect)
{
	RECT tmp;

	for (int i = 0; i < 2; i++)
	{
		if (IntersectRect(&tmp, &Field_Collision[i].GetCollision(), &rect))
		{

		}
	}
	

	return false;
}
