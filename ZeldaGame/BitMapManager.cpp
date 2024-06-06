#include "BitMapManager.h"

BitMapManager* BitMapManager::m_hThis = NULL;

void BitMapManager::Init(HDC hdc)
{

    m_WindowBitMap.Init(hdc, (char*)"Image//Ending//BackGround.bmp");
    m_TitleBitMap      = ImageRoad(hdc,(char*)"Image//Title_Screen//%d.bmp", ImageType_Title);
    m_MenuBitMap       = ImageRoad(hdc, (char*)"Image//Menu//Menu%d.bmp", ImageType_Menu);
    m_ButtonBitMap     = ImageRoad(hdc, (char*)"Image//Button//%d.bmp", ImageType_Button);
    m_BackBitMap       = ImageRoad(hdc, (char*)"Image//Map//Field//Field%d.bmp", ImageType_BackGround);
    m_PlayerHudBitMap  = ImageRoad(hdc, (char*)"Image//HUD//PlayerHUD.bmp", ImageType_HUD);
    m_InventoryBitMap  = ImageRoad(hdc, (char*)"Image//Menu//Inventory//EmptyInven.bmp", ImageType_Inventory);
    m_IvenItemBitMap   = ImageRoad(hdc, (char*)"Image//Menu//Inventory//Item//%d.bmp", ImageType_InvenItem);
    m_NpcBitMap        = ImageRoad(hdc, (char*)"Image//Npc//Npc%d.bmp", ImageType_NPC);
    m_NpcTextBarBitMap = ImageRoad(hdc, (char*)"Image//Npc//Npc_TextBar%d.bmp", ImageType_NPCTextBar);
    m_ItemBitMap       = ImageRoad(hdc, (char*)"Image//Item//Item%d.bmp", ImageType_Item);
    m_DstrObjBitMap    = ImageRoad(hdc, (char*)"Image//Block//DstrObj%d.bmp", ImageType_DstrObj);
    m_CoinBitMap       = ImageRoad(hdc, (char*)"Image//Item//Bonus_Coin%d.bmp", ImageType_Coin);
    //플레이어 방향별 비트맵
    playerDirBitmap.Down_Bitmap   = ImageRoad(hdc, (char*)"Image//Player//DOWN//%d_(1).bmp", ImageType_Player);
    playerDirBitmap.Up_Bitmap     = ImageRoad(hdc, (char*)"Image//Player//UP//%d_(1).bmp", ImageType_Player);
    playerDirBitmap.Left_Bitmap   = ImageRoad(hdc, (char*)"Image//Player//LEFT//%d_(1).bmp", ImageType_Player);
    playerDirBitmap.Right_Bitmap  = ImageRoad(hdc, (char*)"Image//Player//RIGHT//%d_(1).bmp", ImageType_Player);
    
    playerSkillDirBitmap.Up_Bitmap     = ImageRoad(hdc, (char*)"Image//Player//LinkBack%d.bmp", ImageType_Title);
    playerSkillDirBitmap.Down_Bitmap   = ImageRoad(hdc, (char*)"Image//Player//LinkFront%d.bmp", ImageType_Title);
    playerSkillDirBitmap.Left_Bitmap   = ImageRoad(hdc, (char*)"Image//Player//LinkLeft%d.bmp", ImageType_Title);
    playerSkillDirBitmap.Right_Bitmap  = ImageRoad(hdc, (char*)"Image//Player//LinkRight%d.bmp", ImageType_Title);

    m_FieldBitMap[FieldType_Default]         = ImageRoad(hdc, (char*)"Image//Map//Field//Field%d.bmp", ImageType_BackGround);
    m_FieldBitMap[FieldType_Store]           = ImageRoad(hdc, (char*)"Image//Map//Store//Store%d.bmp", ImageType_Store);
    m_FieldBitMap[FieldType_Store_ShoeStroe] = ImageRoad(hdc, (char*)"Image//Map//Store//ShoeStore%d.bmp", ImageType_BackGround);
    m_FieldBitMap[FieldType_Store_StoreRoom] = ImageRoad(hdc, (char*)"Image//Map//Store//StoreRoom%d.bmp", ImageType_BackGround);


    //Thicket0
    
}

void BitMapManager::ChangeFont_TextDraw(HDC backDC, std::string str, int FontSize, int x, int y)
{
    HFONT font, oldFont; // 폰트 

    //폰트사이즈에 맞는 글자와 궁서체로 설정
    font = CreateFont(FontSize, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, 0, TEXT("궁서"));
    oldFont = (HFONT)SelectObject(backDC, font);

    //배경색깔에 맞게 글자색 흰색으로설정
    SetTextColor(backDC, RGB(255, 255, 255));
    //textbox 색깔 검은색으로 설정
    SetBkColor(backDC, RGB(0, 0, 0));
    SetBkMode(backDC, TRANSPARENT);
  

    //글자 테두리 만드는 코드
    TextOutA(backDC, x + 1, y, str.c_str(), str.length());
    TextOutA(backDC, x - 1, y, str.c_str(), str.length());
    TextOutA(backDC, x, y + 1, str.c_str(), str.length());
    TextOutA(backDC, x, y - 1, str.c_str(), str.length());
    SetTextColor(backDC, RGB(0, 0, 0));
    //

    TextOutA(backDC, x, y, str.c_str(), str.size());
 
    //다사용한 oldfont 초기화
    SelectObject(backDC, oldFont);

    //다사용한 폰트 삭제
    DeleteObject(font);

}



BitMap* BitMapManager::ImageRoad(HDC hdc, const char* FileName, ImageType type)
{
    char buf[256];
    int Size = 0;
    switch (type)
    {
    case ImageType_Item:
        Size = 4;
        break;
    case ImageType_NPCTextBar:
        Size = 3;
        break;
    case ImageType_NPC:
        Size = 3;
        break;
    case ImageType_DstrObj:
    case ImageType_Store:
        Size = 2;
        break;
    case ImageType_InvenItem:
        Size = 4;
        break;
    case ImageType_Inventory:
        Size = 1;
        break;
    case ImageType_HUD:
        Size = 1;
        break;
    case ImageType_Button:
        Size = 3;
        break;
    case ImageType_Coin:
    case ImageType_Title:
        Size = 1;
        break;
    case ImageType_Interface:
        break;
    case ImageType_BackGround:
        Size = 1;
        break;
    case ImageType_Player:
        Size = 8;
        break;
    case ImageType_Menu:
        Size = 1;
        break;
    case ImageType_InGame:
        break;
    default:
        break;
    }

    BitMap* BitMapTmp = new BitMap[Size];

    for (int i = 0; i < Size; i++)
    {
        sprintf_s(buf, FileName, i);
        BitMapTmp[i].Init(hdc, buf);
    }

    return BitMapTmp;
}


BitMap* BitMapManager::GetBitMap(ImageType Image) const
{
    switch (Image)
    {
    case ImageType_Coin:
        return m_CoinBitMap;
        break;
    case ImageType_DstrObj:
        return m_DstrObjBitMap;
        break;
    case ImageType_Item:
        return m_ItemBitMap;
        break;
    case ImageType_NPCTextBar:
        return m_NpcTextBarBitMap;
        break;
    case ImageType_NPC:
        return m_NpcBitMap;
        break;
    case ImageType_InvenItem:
        return m_IvenItemBitMap;
        break;
    case ImageType_Inventory:
        return m_InventoryBitMap;
        break;
    case ImageType_HUD:
        return m_PlayerHudBitMap;
        break;
    case ImageType_Button:
        return m_ButtonBitMap;
        break;
    case ImageType_Title:
        return m_TitleBitMap;
        break;
    case ImageType_Interface:
        return m_InterfaceBitMap;
        break;
    case ImageType_Player:
        return NULL;
        break;
    case ImageType_Menu:
        return m_MenuBitMap;
        break;
    case ImageType_InGame:
        return m_InGameBitMap;
        break;
    default:
        break;
    }

    return NULL;
}

