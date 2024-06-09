#include "Field.h"
#include <stdio.h>
#include "GameManager.h"

Field::Field()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			dstrObj* obj = new dstrObj(dstrObjType_Thicket, 145 + (j * 20), 312 + (i * 25));
			AttackableObjects.push_back(obj);
		}
	}
	//578, 363

	wood = new MiniWood(735, 192);

	dstrObj* obj = new dstrObj(dstrObjType_Jar, 145 + 200, 312);
	AttackableObjects.push_back(obj);

	dstrObj* obj1 = new dstrObj(dstrObjType_Jar, 722, 363);
	AttackableObjects.push_back(obj1);
	
	m_BackGround = new BackGround(FieldType_Default);
	NPC = new FieldNPC;

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

	//포탈 콜리전 
	NextField_obstacles = new Obstacle[2];
	NextField_obstacles[0].Init(694, 0, 807, 48);
	NextField_obstacles[1].Init(81, 659, 123, 675);
}

Field::~Field()
{
}

void Field::Init()
{
	Camera::GetInstance()->Init(EndPosition.X, EndPosition.Y);
	GameManager::GetInstance()->GetPlayer()->m_pos = EndPosition;
	Camera::GetInstance()->SetHeight(1024);
}

void Field::Draw(HDC backDC, float DeltaTime)
{
	m_BackGround->Draw(backDC, DeltaTime); // 배경을 그려줌 
	NPC->Draw(backDC, DeltaTime);

	SIZE msize = BitMapManager::GetInstance()->GetWindowSize();
	int  cameraX = Camera::GetInstance()->GetX();
	int  cameraY = Camera::GetInstance()->GetY();
	
	wood->Draw(backDC, DeltaTime);

	for (int i = 0; i < WaterobstacleSize; i++)
	{
		Waterobstacles[i].Draw(backDC, cameraX, cameraY);
	}
	
	
	for (int i = 0; i < obstacleSize; i++)
	{
		obstacles[i].Draw(backDC, cameraX, cameraY);
	}

	for (auto obj : AttackableObjects)
	{
		obj->Draw(backDC, DeltaTime);
	}
	
	for (int i = 0; i < 2; i++)
	{
		NextField_obstacles[i].Draw(backDC, cameraX, cameraY);
	}

}


void Field::Update(float DeltaTime)
{
	m_BackGround->Update(DeltaTime);
	NPC->Update(DeltaTime);
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
			return false;
		}
	}

	for (auto obj : AttackableObjects)
	{
		if (IntersectRect(&tmp, &obj->GetCollision(), &rect))
		{
			if (!obj->Attacked)
				return true;
			else if(!obj->GetCoinPickup())
			{
				GameManager::GetInstance()->GetPlayer()->AddCoin(obj->CoinPickup());
				return false;
			}



		}

	}
	
	if (IntersectRect(&tmp, &NextField_obstacles[0].GetCollision(), &rect)) // 스토어 포탈
	{
		EndPosition = GameManager::GetInstance()->GetPlayer()->m_pos;
		GameManager::GetInstance()->NextField(FieldType_Store);
		return true;
	}

	if (IntersectRect(&tmp, &NextField_obstacles[1].GetCollision(), &rect) && GameManager::GetInstance()->GetPlayer()->GetMini()) // 던전 포탈
	{
		EndPosition = GameManager::GetInstance()->GetPlayer()->m_pos;
		GameManager::GetInstance()->NextField(FieldType_Dungeon);
		GameManager::GetInstance()->GetPlayer()->MiniReset();
		return true;
	}



	NPC->EventCollision(rect);


	return false;
}

dstrObj* Field::AttackableObjects_Collision(RECT rect)
{
	RECT tmp;

	for (auto obj : AttackableObjects)
	{
		if(IntersectRect(&tmp, &obj->GetCollision(), &rect))
		{
			if(!obj->Attacked)
				return obj;		
		}

	}
	return NULL;
}
