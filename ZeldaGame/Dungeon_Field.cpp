#include "Dungeon_Field.h"
#include "GameManager.h"
#include <ctime>
Dungeon_Field::Dungeon_Field()
{
    srand(time(NULL));
    m_BackGround = new BackGround(FieldType_Dungeon);
    EndPosition = { 415, 2500 }; // 2500

    //땅바닥 버튼
    dungeon_Button[0] = new Dungeon_Button(480, 2030, 3, 0);
    dungeon_Button[1] = new Dungeon_Button(800, 1065, 2, 30);
    dungeon_Button[2] = new Dungeon_Button(200, 1065, 3, 30);

    // 횃불 버튼
    dungeon_Button[3] = new Dungeon_Button(210, 500, 2, 0, true, 390);
    dungeon_Button[4] = new Dungeon_Button(210, 730, 2, 0, true, 390);

    Chest[0] = new Treasure_Chest(723, 990);
    Chest[1] = new Treasure_Chest(103, 990);
   
    for (int i = 0; i < 3; i++)
    {
        Object_collision[i] = { 0,0,0,0 };
    }

    RoadBitmap = BitMapManager::GetInstance()->GetBitMap(ImageType_Dungeon_Object)[0];
    DoorBitmap[0] = BitMapManager::GetInstance()->GetBitMap(ImageType_Dungeon_Object)[2];
    DoorBitmap[1] = BitMapManager::GetInstance()->GetBitMap(ImageType_Dungeon_Object)[2];

    int left, top, width, height, frame;
    FILE* fp = fopen("Field4.txt", "rt");
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

    NextField_obstacles->Init(669, 70, 820, 145);


    for (int i = 0; i < MAX_MONSTER_COUNT; i++)
    {
        OctorocMonster* monster = new OctorocMonster;
        octorocMonster[i] = monster;
    }

    octorocMonster[0]->Init(520, 1800, Octoroc_DOWN);
    octorocMonster[1]->Init(50, 1080, Octoroc_DOWN);
    octorocMonster[2]->Init(600, 1080, Octoroc_DOWN);
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
    
    for (int i = 0; i < MAX_BUTTON_COUNT; i++)
    {
        dungeon_Button[i]->Draw(backDC, DeltaTime);

    }


    int  cameraX = Camera::GetInstance()->GetX();
    int  cameraY = Camera::GetInstance()->GetY();
    
    int screenX = (((WINDOWSIZE_WIDTH / 2) - (RoadBitmap.GetSize().cx)) - Camera::GetInstance()->GetX()) + 300;
    int screenY = (((WINDOWSIZE_HEIGHT / 2) - (RoadBitmap.GetSize().cy)) - Camera::GetInstance()->GetY()) + 2005;

    if (dungeon_Button[0]->ButtonCheck())
    {
        Object_collision[0] = {screenX, screenY, screenX + RoadBitmap.GetSize().cx , screenY + RoadBitmap.GetSize().cy};
        //Rectangle(backDC, Object_collision[0].left, Object_collision[0].top, Object_collision[0].right, Object_collision[0].bottom);

        RoadBitmap.AnimationUpdate(backDC, 0, screenX, screenY, RoadBitmap.GetSize(), 1.0F);
    }

    if (!dungeon_Button[1]->ButtonCheck() || !dungeon_Button[2]->ButtonCheck())
    {
        DoorBitmap[0].AnimationUpdate(backDC, 0, screenX + 90, screenY - 975, DoorBitmap[0].GetSize(), 2.0f);
        Object_collision[1] = { screenX + 90, screenY - 975, (screenX + 90) + DoorBitmap[0].GetSize().cx * 2 , (screenY - 975) + DoorBitmap[0].GetSize().cy * 2 };
        //Rectangle(backDC, Object_collision[1].left, Object_collision[1].top, Object_collision[1].right, Object_collision[1].bottom);
    }


    if (!dungeon_Button[3]->ButtonCheck() || !dungeon_Button[4]->ButtonCheck())
    {
        DoorBitmap[1].AnimationUpdate(backDC, 0, screenX + 70, screenY - 1450, DoorBitmap[1].GetSize(), 3.0f);
        Object_collision[2] = { screenX + 70, screenY - 1450, (screenX + 70) + DoorBitmap[1].GetSize().cx * 3 , (screenY - 1450) + DoorBitmap[1].GetSize().cy * 3 };
        //Rectangle(backDC, Object_collision[2].left, Object_collision[2].top, Object_collision[2].right, Object_collision[2].bottom);
    }
   
  

    if (dungeon_Button[1]->ButtonCheck())
    {
         Chest[0]->Draw(backDC, DeltaTime);
    }
   
    if (dungeon_Button[2]->ButtonCheck())
    {
        Chest[1]->Draw(backDC, DeltaTime);
    }

    for (int i = 0; i < WaterobstacleSize; i++)
    {
        Waterobstacles[i].Draw(backDC, cameraX, cameraY);
    }


    NextField_obstacles->Draw(backDC, cameraX, cameraY); //보스 포탈 


    for (int i = 0; i < MAX_MONSTER_COUNT; i++)
    {     
        octorocMonster[i]->Draw(backDC, DeltaTime);
    }

    for (int i = 0; i < obstacleSize; i++) // 벽
    {
        obstacles[i].Draw(backDC, cameraX, cameraY);
    }

}

void Dungeon_Field::Update(float DeltaTime)
{
    RECT tmp;  // 박스 열기 

    for (int i = 0; i < MAX_CHEST_COUNT; i++)
    {
        if (IntersectRect(&tmp, &Chest[i]->GetEvent_Collision(), &GameManager::GetInstance()->GetPlayer()->getCollision()))
        {
            if (GetAsyncKeyState(0x45) & 0x8000) // E 상자 열기
            {
                Chest[i]->BoxOpen = true;
            }

        }
    }

    for (int i = 0; i < MAX_MONSTER_COUNT; i++)
    {
        octorocMonster[i]->Update(DeltaTime);
    }
    
   
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
    for (int i = 0; i < MAX_BUTTON_COUNT; i++)
    {
        dungeon_Button[i]->ButtonCollision(rect);
    }
    RECT tmp;


    for (int i = 0; i < MAX_CHEST_COUNT; i++)
    {
        if (IntersectRect(&tmp, &Chest[i]->GetCollision(), &rect) && !Chest[i]->BoxOpen)  // 박스 오픈시 콜리전 해제 
        {
            return true;
        }
        else if (IntersectRect(&tmp, &Chest[i]->GetCollision(), &rect) && Chest[i]->BoxOpen)
        {
            Chest[i]->Collision();
        }
    }


    if (IntersectRect(&tmp, &Object_collision[0], &rect)) // 길 콜리전
    {
        return false;
    }


    if (!dungeon_Button[1]->ButtonCheck() && !dungeon_Button[2]->ButtonCheck())
    {
        if (IntersectRect(&tmp, &Object_collision[1], &rect)) // 문 콜리전
        {
            return true;
        }
    }

    if (IntersectRect(&tmp, &Object_collision[2], &rect)) // 문 콜리전
    {
        return true;
    }
   

    for (int i = 0; i < WaterobstacleSize; i++) // 추락 콜리전
    {
        if (IntersectRect(&tmp, &Waterobstacles[i].GetCollision(), &rect))
        {
            GameManager::GetInstance()->GetPlayer()->SetPlayerState(PlayerState_FALL);
            return false;
        }
    }

    if (IntersectRect(&tmp, &NextField_obstacles->GetCollision(), &rect)) // 보스 포탈
    {
        EndPosition = GameManager::GetInstance()->GetPlayer()->m_pos;
        GameManager::GetInstance()->NextField(FieldType_Boss);
        return true;
    }


    for (int i = 0; i < MAX_MONSTER_COUNT; i++) // 옥토패스 총알 콜리전
    {
        octorocMonster[i]->Collision(rect);
    }

    for (int i = 0; i < obstacleSize; i++)
    {
        if (IntersectRect(&tmp, &obstacles[i].GetCollision(), &rect))
        {
            return true;
        }
    }
 
    

    return false;
}

void Dungeon_Field::Monsters_Collision(RECT rect)
{
    RECT tmp;

    for (int i = 0; i < MAX_MONSTER_COUNT; i++)
    {
        if (IntersectRect(&tmp, &octorocMonster[i]->GetCollision(), &rect))
        {
            octorocMonster[i]->Hit();
        }
    }
}
