#include "Boss_Field.h"
#include "GameManager.h"

Boss_Field::Boss_Field()
{
    m_BackGround = new BackGround(FieldType_Boss);
    PortalBitmap = m_BackGround->GetBitMap()[1];

    m_BossMonster = new BossMonster;
    EndPosition = { 390,337 };

    int left, top, width, height, frame;
    FILE* fp = fopen("Field5.txt", "rt");
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
}

Boss_Field::~Boss_Field()
{
}

void Boss_Field::Init()
{
    Camera::GetInstance()->Init(EndPosition.X, EndPosition.Y);
    GameManager::GetInstance()->GetPlayer()->m_pos = EndPosition;
    m_BossMonster->Init(550, 200);
}

void Boss_Field::Draw(HDC backDC, float DeltaTime)
{
    m_BackGround->Draw(backDC, DeltaTime);
    m_BossMonster->Draw(backDC, DeltaTime);
    
    int  cameraX = Camera::GetInstance()->GetX();
    int  cameraY = Camera::GetInstance()->GetY();

    for (int i = 0; i < obstacleSize; i++)
    {
        obstacles[i].Draw(backDC, cameraX, cameraY);
    }

    

    if (m_BossMonster->GetDie())
    {
        int screenX = (((WINDOWSIZE_WIDTH / 2) - (PortalBitmap.GetSize().cx * 2)) - Camera::GetInstance()->GetX()) + 500;
        int screenY = (((WINDOWSIZE_HEIGHT / 2) - (PortalBitmap.GetSize().cy * 2)) - Camera::GetInstance()->GetY()) + 100;
        PortalCollision = { screenX, screenY, screenX + PortalBitmap.GetSize().cx * 2 , screenY + PortalBitmap.GetSize().cy * 2 };
        PortalBitmap.AnimationUpdate(backDC, 0, screenX, screenY, PortalBitmap.GetSize(), 2.0f);
        //Rectangle(backDC, PortalCollision.left, PortalCollision.top, PortalCollision.right, PortalCollision.bottom);
    }
  
}

void Boss_Field::Update(float DeltaTime)
{
    m_BossMonster->Update(DeltaTime);

    m_BossMonster->Collision(GameManager::GetInstance()->GetPlayer()->getCollision());
}

void Boss_Field::Reset()
{
}

bool Boss_Field::Collision(RECT rect)
{
    RECT tmp;

    for (int i = 0; i < obstacleSize; i++)
    {
    
        if (IntersectRect(&tmp, &obstacles[i].GetCollision(), &rect))
        {
            return true;
        }

    }

    if (m_BossMonster->GetDie())
    {
        if (IntersectRect(&tmp, &PortalCollision, &rect))
        {
            GameManager::GetInstance()->NextField(FieldType_Ending);
            return false;
        }
    }


    return false;
}

void Boss_Field::Boss_Collision(RECT rect)
{
    RECT tmp;

    if (IntersectRect(&tmp, &m_BossMonster->GetCollision(), &rect))
    {
        m_BossMonster->Hit();
    }
}
