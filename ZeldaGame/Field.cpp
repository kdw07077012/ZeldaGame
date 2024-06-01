#include "Field.h"
#include <stdio.h>
#include "GameManager.h"
Field::Field()
{

	int left, top, width, height, frame;
	FILE* fp = fopen("Field0.txt", "rt");
	fscanf_s(fp, "%d", &frame);
	obstacles = new Obstacle[frame];
	obstacleSize = frame;
	for (int i = 0; i < frame; i++)
	{
		fscanf(fp, "%d %d %d %d", &left, &top, &width, &height);
		obstacles[i].Init(left, top, width, height);
	}

	fscanf_s(fp, "%d", &frame);
	WaterobstacleSize = frame;
	Waterobstacles = new Obstacle[frame];
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

	//m_Rectobstacle[0] = {800 - cameraX, 240 - cameraY,
	//	1270 - cameraX, 324 - cameraY };
	//
	//m_Rectobstacle[1] = { 913 - cameraX, 318 - cameraY,
	//	1064 - cameraX, 387 - cameraY };
	//
	//
	////¾çÂÊº®
	//m_Rectobstacle[2] = { 0 - cameraX, 0 - cameraY,
	//	1493 - cameraX, 80 - cameraY };
	//
	//m_Rectobstacle[3] = { 0 - cameraX, 955 - cameraY,
	//	1500 - cameraX, 1024 - cameraY };
	//
	//m_Rectobstacle[4] = { 0 - cameraX, 180 - cameraY,
	//	30 - cameraX, 1024 - cameraY };
	//
	//m_Rectobstacle[4] = { 1366 - cameraX, 320 - cameraY,
	//	1490 - cameraX, 566 - cameraY };
	//
	//m_Rectobstacle[5] = { 1469 - cameraX, 541 - cameraY,
	//	1500 - cameraX, 1024 - cameraY };
	////
	//m_Rectobstacle[6] = { 941 - cameraX, 388 - cameraY,
	//	1010 - cameraX, 467 - cameraY };
	//m_Rectobstacle[7] = { 818 - cameraX, 481 - cameraY,
	//	1140 - cameraX, 596 - cameraY };
	//m_Rectobstacle[8] = { 818 - cameraX, 481 - cameraY,
	//	1140 - cameraX, 596 - cameraY };
	

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
