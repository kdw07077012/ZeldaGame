#include "Store_Field.h"
#include "GameManager.h"
Store_Field::Store_Field()
{
	m_bShoeStroe = new BackGround(FieldType_Store_ShoeStroe);
	m_bShoeStroe = new BackGround(FieldType_Store_StoreRoom);
	m_BackGround = new BackGround(FieldType_Store);

	NextField_obstacles = new Obstacle[2];
	NextField_obstacles[0].Init(491, 409, 539, 454);
	NextField_obstacles[1].Init(949, 411, 999, 450);

	EndPosition = { 413,413 };
}

Store_Field::~Store_Field()
{
}

void Store_Field::Init()
{
	Camera::GetInstance()->Init(EndPosition.X, EndPosition.Y);
	GameManager::GetInstance()->GetPlayer()->m_pos = EndPosition;
}

void Store_Field::Draw(HDC backDC, float DeltaTime)
{
	m_BackGround[0].Draw(backDC, DeltaTime);

	int  cameraX = Camera::GetInstance()->GetX();
	int  cameraY = Camera::GetInstance()->GetY();

	for (int i = 0; i < 2; i++)
	{
		NextField_obstacles[i].Draw(backDC, cameraX, cameraY);
	}
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

	if (IntersectRect(&tmp, &NextField_obstacles[0].GetCollision(), &rect))
	{
		EndPosition = GameManager::GetInstance()->GetPlayer()->m_pos;
		GameManager::GetInstance()->NextField(FieldType_Store_ShoeStroe);
		
		return true;
	}

	if (IntersectRect(&tmp, &NextField_obstacles[1].GetCollision(), &rect))
	{
		EndPosition = GameManager::GetInstance()->GetPlayer()->m_pos;
		GameManager::GetInstance()->NextField(FieldType_Store_StoreRoom);
		
		return true;
	}
	

	return false;
}
