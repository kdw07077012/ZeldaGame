#include "ShoeStroe_Field.h"
#include "GameManager.h"
ShoeStroe_Field::ShoeStroe_Field()
{
    m_BackGround = new BackGround(FieldType_Store_ShoeStroe);

    NextField_obstacles = new Obstacle[1];
    NextField_obstacles->Init(689, 763, 843, 808);
	EndPosition = { 413,413 };
}

ShoeStroe_Field::~ShoeStroe_Field()
{
}

void ShoeStroe_Field::Init()
{
	Camera::GetInstance()->Init(EndPosition.X, EndPosition.Y);
	GameManager::GetInstance()->GetPlayer()->m_pos = EndPosition;
}

void ShoeStroe_Field::Draw(HDC backDC, float DeltaTime)
{
    m_BackGround->Draw(backDC, DeltaTime);

	int  cameraX = Camera::GetInstance()->GetX();
	int  cameraY = Camera::GetInstance()->GetY();

    NextField_obstacles[0].Draw(backDC, cameraX, cameraY);
}

void ShoeStroe_Field::Update(float DeltaTime)
{

}

void ShoeStroe_Field::Reset()
{
}

bool ShoeStroe_Field::Collision(RECT rect)
{
	RECT tmp;

	if (IntersectRect(&tmp, &NextField_obstacles[0].GetCollision(), &rect))
	{
		GameManager::GetInstance()->NextField(FieldType_Store);
		return true;
	}

	return false;
}
