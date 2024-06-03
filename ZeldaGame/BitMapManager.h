#pragma once
#include "BitMap.h"

#include <string>
enum ImageType // �̹��� Ÿ���� ���� �ҷ���
{
	ImageType_Title,
	ImageType_Interface,
	ImageType_BackGround,
	ImageType_Store,
	ImageType_Player,
	ImageType_Menu,
	ImageType_InGame,
	ImageType_Button,
	ImageType_HUD,
	ImageType_Inventory,
	ImageType_Item,
};

enum FieldType
{
	FieldType_Default,  // �⺻��ŸƮ ��
	FieldType_Store,    // ���� �� 
	FieldType_Store_ShoeStroe, // ���� �� �� �Ź� ����
	FieldType_Store_StoreRoom, // ���� �� �� ����� 
	FieldType_Dungeon,
	FieldType_Boss,
	End_Field,
};

struct PlayerDirBitmap // �÷��̾� ���⺰ �ִϸ��̼��� ���� ����ü
{
	BitMap* Left_Bitmap;
	BitMap* Right_Bitmap;
	BitMap* Up_Bitmap;
	BitMap* Down_Bitmap;
};


class BitMapManager
{
private:
	static BitMapManager* m_hThis; // �̱��� ��� 

	BitMap m_WindowBitMap;

	BitMap* m_ButtonBitMap;		// ��ư �̹���
	BitMap* m_TitleBitMap;		// Ÿ��Ʋ �̹���
	BitMap* m_BackBitMap;		// ��� �̹���
	BitMap* m_InterfaceBitMap;  //�������̽� UI �̹���
	BitMap* m_MenuBitMap;	    // �޴� �̹���
	BitMap* m_InGameBitMap;		//�ΰ��� �̹���
	BitMap* m_PlayerHudBitMap;  // HUD �̹���  
	BitMap* m_InventoryBitMap;  // HUD �̹���  
	BitMap* m_ItemBitMap;	    // ������ �̹��� 
	BitMap* m_FieldBitMap[End_Field];	// �� �̹���

	PlayerDirBitmap playerDirBitmap;	    // �÷��̾� ���⺰�̹���

public:
	static BitMapManager* GetInstance() // �̱���
	{
		if (m_hThis == NULL)
			m_hThis = new BitMapManager;

		return m_hThis;
	}

	void Init(HDC hdc);

	BitMap* ImageRoad(HDC hdc, const char* FileName, ImageType type); // Ÿ���� �̹��� �ε�
	BitMap* GetBitMap(ImageType Image) const; 					 // �ش� Ÿ���� �̹��� ��ȯ
	SIZE GetWindowSize() const { return m_WindowBitMap.GetSize(); }  // ������ ������ ��ȯ
	BitMap GetWindowBitMap() const { return m_WindowBitMap; }
	PlayerDirBitmap GetPlayerDirBitmap() const { return playerDirBitmap; }

	BitMap* GetBackGroundBitMap(FieldType Image) const {
		return m_FieldBitMap[Image];
	}

};

