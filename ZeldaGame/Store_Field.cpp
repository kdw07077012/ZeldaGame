#include "Store_Field.h"
#include "GameManager.h"
Store_Field::Store_Field()
{
	m_bShoeStroe = new BackGround(FieldType_Store_ShoeStroe);
	m_bShoeStroe = new BackGround(FieldType_Store_StoreRoom);
	m_BackGround = new BackGround(FieldType_Store);

	NextField_obstacles = new Obstacle[3];

	int left, top, width, height, frame;
	FILE* fp = fopen("Field1.txt", "rt");
	fscanf_s(fp, "%d", &frame);
	obstacles = new Obstacle[frame];
	obstacleSize = frame;

	// 메모장에 있는 맵 콜리전 정보를 가져옴
	for (int i = 0; i < frame; i++)
	{
		fscanf(fp, "%d %d %d %d", &left, &top, &width, &height);
		obstacles[i].Init(left, top, width, height);
	}


	fclose(fp);
	
	NextField_obstacles[0].Init(491, 409, 539, 454);
	NextField_obstacles[1].Init(949, 411, 999, 450);
	NextField_obstacles[2].Init(647, 967, 840, 1015);
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
	m_BackGround->Draw(backDC, DeltaTime);


	int  cameraX = Camera::GetInstance()->GetX();
	int  cameraY = Camera::GetInstance()->GetY();



	for (int i = 0; i < 3; i++)
	{
		NextField_obstacles[i].Draw(backDC, cameraX, cameraY);
	}

	for (int i = 0; i < obstacleSize; i++)
	{
		obstacles[i].Draw(backDC, cameraX, cameraY);
	}
}

void Store_Field::Update(float DeltaTime)
{
}

void Store_Field::BackDraw(HDC backDC, float DeltaTime)
{
	
	SIZE size = { 255,181 };
	int screenX = (((WINDOWSIZE_WIDTH / 2) - (size.cx)) - Camera::GetInstance()->GetX()) + 510;
	int screenY = (((WINDOWSIZE_HEIGHT / 2) - (size.cy)) - Camera::GetInstance()->GetY()) + 600;

	m_BackGround->GetBitMap()[1].CutDraw(backDC, screenX, screenY, 0,0,size);
}

void Store_Field::Reset()
{
}

bool Store_Field::Collision(RECT rect)
{
	RECT tmp;

	for (int i = 0; i < obstacleSize; i++)
	{
		if (IntersectRect(&tmp, &obstacles[i].GetCollision(), &rect))
		{
			return true;
		}
	}

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

	if (IntersectRect(&tmp, &NextField_obstacles[2].GetCollision(), &rect))
	{
		EndPosition = GameManager::GetInstance()->GetPlayer()->m_pos;
		GameManager::GetInstance()->NextField(FieldType_Default);

		return true;
	}
	

	return false;
}
