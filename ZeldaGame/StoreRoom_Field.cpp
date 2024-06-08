#include "StoreRoom_Field.h"
#include "GameManager.h"

StoreRoom_Field::StoreRoom_Field()
{
    m_BackGround = new BackGround(FieldType_Store_StoreRoom);
    TextBarBitMap = BitMapManager::GetInstance()->GetBitMap(ImageType_ItemTextBar);
    Npc = new StoreNPC;
    for (int i = 0; i < 4; i++) // 상점 아이템 배치
    {
        Item* item = new Item(EItem(i), 140 + (50 * i), 127, ItemImageType_InGame);
        RECT rect = { 0,0,0,0 };
        
        Items.push_back(item);
    }

    int left, top, width, height, frame;
    FILE* fp = fopen("Field3.txt", "rt");
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
  
    NextField_obstacles = new Obstacle[1];
    NextField_obstacles->Init(682, 778, 797, 835);
    EndPosition = { 413,413 };
    itembarDraw = false;
    ItemPrice[0] = 100;
    ItemPrice[1] = 100;
    ItemPrice[2] = 50;
    ItemPrice[3] = 10;
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

   
    
    for (int i = 0; i < obstacleSize; i++)
    {
        obstacles[i].Draw(backDC, cameraX, cameraY);
    }

    Npc->Draw(backDC, DeltaTime);

    for (Item* item : Items)
    {
        item->Draw(backDC, DeltaTime);   
    }

    if (itembarDraw)
        TextBarBitMap[itembarCount].CutDraw(backDC, 130, 400, 0, 0, TextBarBitMap->GetSize(), 0.8f);
      
}

void StoreRoom_Field::Update(float DeltaTime)
{
    Npc->Update(DeltaTime);


    if (GetAsyncKeyState(0x45) & 0x8000) // E키
    {
        if (itembarDraw)
        {
            GameManager::GetInstance()->StoreItemBuy((InGame_Item)itembarCount, ItemPrice[itembarCount]);
        }
    }

}

void StoreRoom_Field::Reset()
{
}

bool StoreRoom_Field::Collision(RECT rect)
{
    RECT tmp;
    

    for (int i = 0; i < obstacleSize; i++)
    {
        if (IntersectRect(&tmp, &obstacles[i].GetCollision(), &rect))
        {
            return true;
        }
    }

    for (Item* item : Items)
    {
        if (IntersectRect(&tmp, &item->GetCollision(), &rect))
        {
            itembarDraw = true;
            itembarCount = item->item;
            break;
        }
        else
        {
            itembarDraw = false;
        }
          
    }


    if (IntersectRect(&tmp, &NextField_obstacles[0].GetCollision(), &rect))
    {
        GameManager::GetInstance()->NextField(FieldType_Store);
        return true;
    }

    if (Npc->EventCollision(rect))
        return true;

    return false;
}
