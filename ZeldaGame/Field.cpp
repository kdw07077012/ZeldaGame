#include "Field.h"

Field::Field()
{
}

Field::~Field()
{
}

void Field::Draw(HDC backDC, float DeltaTime)
{
	SIZE msize = BitMapManager::GetInstance()->GetWindowSize();

	Rectangle(backDC, 800 - Camera::GetInstance()->GetX(), 240 - Camera::GetInstance()->GetY(),
		1270 - Camera::GetInstance()->GetX(), 324 - Camera::GetInstance()->GetY());

	test_rect = { 800 - Camera::GetInstance()->GetX(), 240 - Camera::GetInstance()->GetY(),
		1270 - Camera::GetInstance()->GetX(), 324 - Camera::GetInstance()->GetY() };
}

void Field::Update(float DeltaTime)
{
	
}

void Field::Reset()
{
}

bool Field::Collision(RECT rect)
{
	RECT tmp;

	if (IntersectRect(&tmp, &test_rect, &rect))
	{
		return true;
	}

	return false;
}
