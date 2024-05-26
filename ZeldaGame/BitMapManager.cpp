#include "BitMapManager.h"

BitMapManager* BitMapManager::m_hThis = NULL;

void BitMapManager::Init(HDC hdc)
{

    m_WindowBitMap.Init(hdc, (char*)"Image//Ending//BackGround.bmp");
    m_TitleBitMap = ImageRoad(hdc,(char*)"Image//Title_Screen//%d.bmp", ImageType_Title);
    m_MenuBitMap = ImageRoad(hdc, (char*)"Image//Menu//Menu%d.bmp", ImageType_Menu);

}



BitMap* BitMapManager::ImageRoad(HDC hdc, const char* FileName, ImageType type)
{
    char buf[256];
    int Size = 0;
    switch (type)
    {
    case ImageType_Title:
        Size = 1;
        break;
    case ImageType_Interface:
        break;
    case ImageType_BackGround:
        break;
    case ImageType_Player:
        Size = 1;
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
    case ImageType_Title:
        return m_TitleBitMap;
        break;
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
