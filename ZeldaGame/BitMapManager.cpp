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
    m_IvenItemBitMap   = ImageRoad(hdc, (char*)"Image//Menu//Inventory//Item//Inven_%d.bmp", ImageType_InvenItem);
    m_NpcBitMap        = ImageRoad(hdc, (char*)"Image//Npc//Npc%d.bmp", ImageType_NPC);
    m_NpcTextBarBitMap = ImageRoad(hdc, (char*)"Image//Npc//Npc_TextBar%d.bmp", ImageType_NPCTextBar);
    m_ItemBitMap       = ImageRoad(hdc, (char*)"Image//Item//Item%d.bmp", ImageType_Item);
    m_DstrObjBitMap    = ImageRoad(hdc, (char*)"Image//Block//DstrObj%d.bmp", ImageType_DstrObj);
    m_CoinBitMap       = ImageRoad(hdc, (char*)"Image//Item//Bonus_Coin%d.bmp", ImageType_Coin);
    m_ChooseItemBitMap = ImageRoad(hdc, (char*)"Image//Menu//Inventory//Item//Choose_Item%d.bmp", ImageType_Choose_Item);
    m_ItemTextBarBitMap = ImageRoad(hdc, (char*)"Image//Map//Store//TextBar//Text_%d.bmp", ImageType_ItemTextBar);
    m_LinkHpBitMap     = ImageRoad(hdc, (char*)"Image//HUD//LinkHp.bmp", ImageType_LikHp);
    m_MiniWoodBitmap   = ImageRoad(hdc, (char*)"Image//Mini//Wood%d.bmp", ImageType_MiniWood);
    m_PlayerMiniBitMap = ImageRoad(hdc, (char*)"Image//Mini//Player_Mini%d.bmp", ImageType_PlayerMini);
    m_PlayerMiniChangeBitMap = ImageRoad(hdc, (char*)"Image//Player//Player_MiniChange%d.bmp", ImageType_Player_MiniChange);
    m_TreasureChestBitmap = ImageRoad(hdc, (char*)"Image//Block//Treasure_Chest%d.bmp", ImageType_Treasure_Chest);
    m_DungeonObjectBitmap = ImageRoad(hdc, (char*)"Image//Map//Dungeon//Dungeon_Object%d.bmp", ImageType_Dungeon_Object);
    m_PlayerFallBitmap  = ImageRoad(hdc, (char*)"Image//Player//Player_FALL%d.bmp", ImageType_Player_FALL);


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
    m_FieldBitMap[FieldType_Dungeon]         = ImageRoad(hdc, (char*)"Image//Map//Dungeon//DunGeon%d.bmp", ImageType_Dungeon);
    m_FieldBitMap[FieldType_Boss]            = ImageRoad(hdc, (char*)"Image//Map//BossStage//BossMap%d.bmp", ImageType_Dungeon);

    m_MonsterBitMap  = ImageRoad(hdc, (char*)"Image//Monster//Monster%d.bmp", ImageType_Monster);

    m_QuestMenuBitMap =  ImageRoad(hdc, (char*)"Image//Menu//Inventory//Quest_Menu%d.bmp", ImageType_QuestMenu);
    m_QuestListBitMap = ImageRoad(hdc, (char*)"Image//Quest//Quest%d.bmp", ImageType_QuestList);


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
    case ImageType_Monster:
        Size = 1;
        break;
    case ImageType_Dungeon_Object:
    case ImageType_ItemTextBar:
    case ImageType_Item:
        Size = 4;
        break;
    case ImageType_NPCTextBar:
        Size = 3;
        break;
    case ImageType_NPC:
        Size = 3;
        break;  
    case ImageType_Dungeon:
    case ImageType_DstrObj:
    case ImageType_Store:
        Size = 2;
        break;
    case ImageType_InvenItem:
        Size = 6;
        break;
    case ImageType_Inventory:
        Size = 1;
        break;
    case ImageType_HUD:
        Size = 1;
        break;
    case ImageType_QuestList:
    case ImageType_Button:
        Size = 3;
        break;
    case ImageType_Player_FALL:
    case ImageType_Treasure_Chest:
    case ImageType_QuestMenu:
    case ImageType_Player_MiniChange:
    case ImageType_PlayerMini:
    case ImageType_MiniWood:
    case ImageType_LikHp:
    case ImageType_Choose_Item:
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
    case ImageType_Player_FALL:
        return m_PlayerFallBitmap;
        break;
    case ImageType_Dungeon_Object:
        return m_DungeonObjectBitmap;
        break;
    case ImageType_Treasure_Chest:
        return m_TreasureChestBitmap;
        break;
    case ImageType_QuestList:
        return m_QuestListBitMap;
        break;
    case ImageType_QuestMenu:
        return m_QuestMenuBitMap;
        break;
    case ImageType_Monster:
        return m_MonsterBitMap;
        break;
    case ImageType_Player_MiniChange:
        return m_PlayerMiniChangeBitMap;
        break;
    case ImageType_PlayerMini:
        return m_PlayerMiniBitMap;
        break;
    case ImageType_MiniWood:
        return m_MiniWoodBitmap;
        break;
    case ImageType_LikHp:
        return m_LinkHpBitMap;
        break;
    case ImageType_ItemTextBar:
        return m_ItemTextBarBitMap;
        break;
    case ImageType_Choose_Item:
        return m_ChooseItemBitMap;
        break;
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

