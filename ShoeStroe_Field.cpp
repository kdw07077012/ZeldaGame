#include "ShoeStroe_Field.h"
#include "GameManager.h"
ShoeStroe_Field::ShoeStroe_Field()
{
    m_BackGround = new BackGround(FieldType_Store_ShoeStroe);
	m_NPC = new ShoeNPC;
    NextField_obstacles = new Obstacle[1];
    NextField_obstacles->Init(689, 763, 843, 808);
	EndPosition = { 413,413 };

	Chest = new Treasure_Chest(550, 380); // 보물상자 드로우
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

	m_NPC->Draw(backDC, DeltaTime);

	if (m_NPC->GetQuest()->GetComplete())
	{
		Chest->Draw(backDC, DeltaTime);
	}
}

void ShoeStroe_Field::Update(float DeltaTime)
{
	m_NPC->Update(DeltaTime);

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

void ShoeStroe_Field::Reset()
{
	Chest->Reset();
	m_NPC->Reset();
}

NPC* ShoeStroe_Field::FieldNpcCollision(RECT rect)
{
	if (m_NPC->EventCollision(rect))
		return m_NPC;

	return NULL;
}

bool ShoeStroe_Field::Collision(RECT rect)
{
	RECT tmp;

	if (IntersectRect(&tmp, &NextField_obstacles[0].GetCollision(), &rect))
	{
		GameManager::GetInstance()->NextField(FieldType_Store);
		return true;
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


	return false;
}
