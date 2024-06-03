#include "StoreRoom_Field.h"
#include "GameManager.h"

StoreRoom_Field::StoreRoom_Field()
{
    m_BackGround = new BackGround(FieldType_Store_StoreRoom);
    NextField_obstacles = new Obstacle[1];
    NextField_obstacles->Init(682, 778, 797, 835);
    EndPosition = { 413,413 };
}

StoreRoom_Field::~StoreRoom_Field()
{
}

void StoreRoom_Field::Init()
{
    Camera::GetInstance()->Init(EndPosition.X, EndPosition.Y);
    GameManager::GetInstance()->GetPlayer()->m_pos = EndPosition;
}

void StoreRoom_Field::Draw(HDC backDC, float DeltaTime)
{
    m_BackGround->Draw(backDC, DeltaTime);

    int  cameraX = Camera::GetInstance()->GetX();
    int  cameraY = Camera::GetInstance()->GetY();

    NextField_obstacles[0].Draw(backDC, cameraX, cameraY);

    
}

void StoreRoom_Field::Update(float DeltaTime)
{
}

void StoreRoom_Field::Reset()
{
}

bool StoreRoom_Field::Collision(RECT rect)
{
    RECT tmp;
    

    if (IntersectRect(&tmp, &NextField_obstacles[0].GetCollision(), &rect))
    {
        GameManager::GetInstance()->NextField(FieldType_Store);
        return true;
    }

    return false;
}
