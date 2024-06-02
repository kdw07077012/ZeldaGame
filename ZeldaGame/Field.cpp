#include "Field.h"
#include <stdio.h>
#include "GameManager.h"
Field::Field()
{
	//m_BackGround = new BackGround;


	int left, top, width, height, frame;
	FILE* fp = fopen("Field0.txt", "rt");
	fscanf_s(fp, "%d", &frame);
	obstacles = new Obstacle[frame];
	obstacleSize = frame;
	// 메모장에 있는 맵 콜리전 정보를 가져옴
	for (int i = 0; i < frame; i++)
	{
		fscanf(fp, "%d %d %d %d", &left, &top, &width, &height);
		obstacles[i].Init(left, top, width, height);
	}
	fscanf_s(fp, "%d", &frame);
	WaterobstacleSize = frame;
	Waterobstacles = new Obstacle[frame];
	// 강 콜리전을 정보를 가져옴
	for (int i = 0; i < frame; i++)
	{
		fscanf(fp, "%d %d %d %d", &left, &top, &width, &height);
		Waterobstacles[i].Init(left, top, width, height);
	}

	fclose(fp);
}

Field::~Field()
{
}

void Field::Draw(HDC backDC, float DeltaTime)
{
	SIZE msize = BitMapManager::GetInstance()->GetWindowSize();
	int  cameraX = Camera::GetInstance()->GetX();
	int  cameraY = Camera::GetInstance()->GetY();
	
	for (int i = 0; i < WaterobstacleSize; i++)
	{
		Waterobstacles[i].Draw(backDC, cameraX, cameraY);
	}
	
	
	for (int i = 0; i < obstacleSize; i++)
	{
		obstacles[i].Draw(backDC, cameraX, cameraY);
	}

	

}

void Field::Update(float DeltaTime)
{
	
}

//0 955
void Field::Reset()
{
}

bool Field::Collision(RECT rect)
{
	RECT tmp;
	//Waterobstacles

	for (int i = 0; i < obstacleSize; i++)
	{
		if (IntersectRect(&tmp, &obstacles[i].GetCollision(), &rect))
		{
			return true;
		}
	}


	for (int i = 0; i < WaterobstacleSize; i++)
	{
		if (IntersectRect(&tmp, &Waterobstacles[i].GetCollision(), &rect))
		{
			GameManager::GetInstance()->GetPlayer()->SetPlayerState(PlayerState_FALLWATER);
		}
	}
	


	return false;
}
