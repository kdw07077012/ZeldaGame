#include "Dungeon_Field.h"
#include "GameManager.h"
Dungeon_Field::Dungeon_Field()
{
    m_BackGround = new BackGround(FieldType_Dungeon);
    EndPosition = { 415, 2500 };
}

Dungeon_Field::~Dungeon_Field()
{
}

void Dungeon_Field::Init()
{
    Camera::GetInstance()->Init(EndPosition.X, EndPosition.Y);
    GameManager::GetInstance()->GetPlayer()->m_pos = EndPosition;
    Camera::GetInstance()->SetHeight(3084);
}

void Dungeon_Field::Draw(HDC backDC, float DeltaTime)
{
    m_BackGround->Draw(backDC, DeltaTime);
}

void Dungeon_Field::Update(float DeltaTime)
{
}

void Dungeon_Field::BackDraw(HDC backDC, float DeltaTime)
{
    int screenX = Camera::GetInstance()->GetX();
    int screenY =  Camera::GetInstance()->GetY();

    m_BackGround->GetBitMap()[1].Draw(backDC, -screenX, -screenY, 1);
}

void Dungeon_Field::Reset()
{
}

bool Dungeon_Field::Collision(RECT rect)
{
    return false;
}
