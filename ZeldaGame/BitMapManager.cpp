#include "BitMapManager.h"

BitMapManager* BitMapManager::m_hThis = NULL;

void BitMapManager::Init(HDC hdc)
{

    m_WindowBitMap.Init(hdc, (char*)"Image//Ending//BackGround.bmp");
    m_TitleBitMap = ImageRoad(hdc,(char*)"Image//Title_Screen//%d.bmp", ImageType_Title);
    m_MenuBitMap = ImageRoad(hdc, (char*)"Image//Menu//Menu%d.bmp", ImageType_Menu);
    m_ButtonBitMap = ImageRoad(hdc, (char*)"Image//Button//%d.bmp", ImageType_Button);
    m_BackBitMap = ImageRoad(hdc, (char*)"Image//Map//Field//Field%d.bmp", ImageType_BackGround);
    m_PlayerHudBitMap = ImageRoad(hdc, (char*)"Image//HUD//PlayerHUD.bmp", ImageType_HUD);
    m_InventoryBitMap = ImageRoad(hdc, (char*)"Image//Menu//Inventory//EmptyInven.bmp", ImageType_Inventory);
    m_ItemBitMap = ImageRoad(hdc, (char*)"Image//Menu//Inventory//Item//%d.bmp", ImageType_Item);

    //플레이어 방향별 비트맵
    playerDirBitmap.Down_Bitmap = ImageRoad(hdc, (char*)"Image//Player//DOWN//%d_(1).bmp", ImageType_Player);
    playerDirBitmap.Up_Bitmap = ImageRoad(hdc, (char*)"Image//Player//UP//%d_(1).bmp", ImageType_Player);
    playerDirBitmap.Left_Bitmap = ImageRoad(hdc, (char*)"Image//Player//LEFT//%d_(1).bmp", ImageType_Player);
    playerDirBitmap.Right_Bitmap = ImageRoad(hdc, (char*)"Image//Player//RIGHT//%d_(1).bmp", ImageType_Player);


    m_FieldBitMap[Default_Field] = ImageRoad(hdc, (char*)"Image//Map//Field//Field%d.bmp", ImageType_BackGround);
    m_FieldBitMap[Store_Field] = ImageRoad(hdc, (char*)"Image//Map//Store//Store%d.bmp", ImageType_BackGround);

    
    
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
    case ImageType_Inventory:
        Size = 1;
        break;
    case ImageType_HUD:
        Size = 1;
        break;
    case ImageType_Button:
        Size = 3;
        break;
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
    case ImageType_Item:
        return m_ItemBitMap;
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

