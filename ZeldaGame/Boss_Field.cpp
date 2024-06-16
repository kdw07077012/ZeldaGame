#include "Boss_Field.h"
#include "GameManager.h"

Boss_Field::Boss_Field()
{
    m_BackGround = new BackGround(FieldType_Boss);
    EndPosition = { 390,337 };
}

Boss_Field::~Boss_Field()
{
}

void Boss_Field::Init()
{
    Camera::GetInstance()->Init(EndPosition.X, EndPosition.Y);
    GameManager::GetInstance()->GetPlayer()->m_pos = EndPosition;
}

void Boss_Field::Draw(HDC backDC, float DeltaTime)
{
    m_BackGround->Draw(backDC, DeltaTime);
}

void Boss_Field::Update(float DeltaTime)
{
}

void Boss_Field::Reset()
{
}

bool Boss_Field::Collision(RECT rect)
{
    return false;
}
