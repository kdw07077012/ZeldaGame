#include "BitMapManager.h"

BitMapManager* BitMapManager::m_hThis = NULL;

void BitMapManager::Init(HDC hdc)
{

    m_WindowBitMap.Init(hdc, (char*)"Image//Title_Screen//BackGround.bmp");

    //m_PlayerBitMap->Init(hdc, (char*)"Image//Player//LEFT//Player_WALK.bmp");
}



BitMap* BitMapManager::ImageRoad(HDC hdc, const char* FileName, ImageType type)
{
    char buf[256];
    int Size = 0;
    switch (type)
    {
    case ImageType_Interface:
        break;
    case ImageType_BackGround:
        break;
    case ImageType_Player:
        Size = 1;
        break;
    case ImageType_Menu:
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
    case ImageType_Interface:
        return m_InterfaceBitMap;
        break;
    case ImageType_BackGround:
        return m_BackBitMap;
        break;
    case ImageType_Player:
        return m_PlayerBitMap;
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
