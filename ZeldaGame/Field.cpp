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
	m_NPC = new FieldNPC;

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


	for (int i = 0; i < SNAKE_SIZE; i++)
	{
		SnakeMonster* Snake = new SnakeMonster;
		m_Snake[i] = Snake;
	}

	m_Snake[0]->Init(400, 400);
	m_Snake[1]->Init(870, 400);
	m_Snake[2]->Init(950,-160);
	m_Snake[3]->Init(746, 163);

	Chest = new Treasure_Chest(550, 450); // 보물상자 드로우
}

Field::~Field()
{
}

void Field::Init()
{
	Camera::GetInstance()->Init(EndPosition.X, EndPosition.Y);
	GameManager::GetInstance()->GetPlayer()->m_pos = EndPosition;
	Camera::GetInstance()->SetHeight(1024);
	Reset();

	
}

void Field::Draw(HDC backDC, float DeltaTime)
{
	m_BackGround->Draw(backDC, DeltaTime); // 배경을 그려줌 
	m_NPC->Draw(backDC, DeltaTime);

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

	for (int i = 0; i < SNAKE_SIZE; i++)
	{
		m_Snake[i]->Draw(backDC, DeltaTime);
	}


	if (m_NPC->GetQuest()->GetComplete())
	{
		Chest->Draw(backDC, DeltaTime);
	}
	
}


void Field::Update(float DeltaTime)
{
	m_BackGround->Update(DeltaTime);
	m_NPC->Update(DeltaTime);

	for (int i = 0; i < SNAKE_SIZE; i++)
	{
		m_Snake[i]->Update(DeltaTime);
		m_Snake[i]->Collision(GameManager::GetInstance()->GetPlayer()->getCollision());
	}

	RECT tmp;  // 박스 열기 
	if (IntersectRect(&tmp, &Chest->GetEvent_Collision(), &GameManager::GetInstance()->GetPlayer()->getCollision()) && 
		m_NPC->GetQuest()->GetComplete())
	{
		if (GetAsyncKeyState(0x45) & 0x8000) // E 상자 열기
		{
			Chest->BoxOpen = true;
		}
		
	}
}
	

//0 955
void Field::Reset()
{
	m_Snake[0]->Init(400, 400);
	m_Snake[1]->Init(870, 400);
	m_Snake[2]->Init(950, -160);
	m_Snake[3]->Init(746, 163);

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


	for (int i = 0; i < WaterobstacleSize; i++) // 강 콜리전
	{
		if (IntersectRect(&tmp, &Waterobstacles[i].GetCollision(), &rect))
		{
			GameManager::GetInstance()->GetPlayer()->SetPlayerState(PlayerState_FALLWATER);
			return false;
		}
	}

	for (auto obj : AttackableObjects) // 파괴 오브젝트 풀, 항아리 체크
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

	if (m_NPC->GetQuest()->GetComplete())
	{
		if (IntersectRect(&tmp, &Chest->GetCollision(), &rect) && !Chest->BoxOpen)  // 박스 오픈시 콜리전 해제 
		{
			return true;
		}
		else if (IntersectRect(&tmp, &Chest->GetCollision(), &rect) && Chest->BoxOpen)
		{
			Chest->Collision();
		}
	}

	


	//GameManager::GetInstance()->GetPlayer()->AddCoin(obj->CoinPickup());


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

	

	return false;
}

NPC* Field::FieldNpcCollision(RECT rect)
{
	if (m_NPC->EventCollision(rect)) // npc 콜리전
	{
		return m_NPC;
	}

	return NULL;

}

void Field::MiniChangeWood_Collision(RECT rect)
{
	RECT tmp;

	if (IntersectRect(&tmp, &wood->GetCollision(), &rect)) // 미니 변신 나무 
	{
		GameManager::GetInstance()->GetPlayer()->MiniModeChange(735, 168); // 나무의 현좌표값 넘겨줌
	}	
}

void Field::InputCheck(int vKey)
{

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

void Field::Monsters_Collision(RECT rect)
{
	RECT tmp;

	for (int i = 0; i < SNAKE_SIZE; i++)
	{
		if (IntersectRect(&tmp, &m_Snake[i]->GetCollision(), &rect))
		{
			m_Snake[i]->Hit();
		}
	}
	
}
