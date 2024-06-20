#include "Ending_Field.h"
#include "GameManager.h"

Ending_Field::Ending_Field()
{
    m_BackGround = new BackGround(FieldType_Ending);
    ZeldaBitmap = BitMapManager::GetInstance()->GetInstance()->GetBitMap(ImageType_Zelda);
    EndPosition = { 413,500 };
    m_OneSize = { 200, 200 };
    ZeldaCollision = { 0,0,0,0 };
    AnimDeltaTime = 0.0f;
    bReset = true;
}

Ending_Field::~Ending_Field()
{
}

void Ending_Field::Init()
{
    Camera::GetInstance()->Init(EndPosition.X, EndPosition.Y);
    GameManager::GetInstance()->GetPlayer()->m_pos = EndPosition;
}

void Ending_Field::Draw(HDC backDC, float DeltaTime)
{
    m_BackGround->Draw(backDC, DeltaTime);
}

void Ending_Field::Update(float DeltaTime)
{
    if (bReset)
    {
        Camera::GetInstance()->Init(EndPosition.X, EndPosition.Y);
        GameManager::GetInstance()->GetPlayer()->m_pos = EndPosition;
        bReset = false;
    }

    m_ScreenX = (((WINDOWSIZE_WIDTH / 2) - (m_OneSize.cx)) - Camera::GetInstance()->GetX()) + 520;
    m_ScreenY = (((WINDOWSIZE_HEIGHT / 2) - (m_OneSize.cy)) - Camera::GetInstance()->GetY()) - 50;

    ZeldaCollision = { m_ScreenX , m_ScreenY, m_ScreenX + 140, m_ScreenY + 140 };

    if (bCollision)
    {
        AnimDeltaTime += DeltaTime;

        if (AnimDeltaTime > 0.1f)
        {
            if (AnimCount + 1 >= 20)
            {
                DelayTime += DeltaTime;

                if (DelayTime > 0.1f)
                {
                    GameManager::GetInstance()->NextField(FieldType_ending_credits);
                }
         
            }
            else
                AnimCount++;

            AnimDeltaTime = 0.0f;
        }
    }
    
}

void Ending_Field::BackDraw(HDC backDC, float DeltaTime)
{
    int screenX = Camera::GetInstance()->GetX();
    int screenY = Camera::GetInstance()->GetY();

    m_BackGround->GetBitMap()[1].Draw(backDC, -screenX, -screenY, 1);

    
    ZeldaBitmap->AnimationUpdate(backDC, AnimCount ,m_ScreenX, m_ScreenY, m_OneSize, 0.7f, 0);
    //Rectangle(backDC, ZeldaCollision.left, ZeldaCollision.top, ZeldaCollision.right, ZeldaCollision.bottom);
}

void Ending_Field::Reset()
{
}

bool Ending_Field::Collision(RECT rect)
{
    RECT tmp;

    if (IntersectRect(&tmp, &ZeldaCollision, &rect))
    {
        bCollision = true;
    }


    return false;
}
