#pragma once
#include "BitMap.h"
#include <string>

#define WINDOWSIZE_WIDTH 720
#define WINDOWSIZE_HEIGHT 540

//#define DEBUG // �ݸ��� �ؽ�Ʈ�� ����� 
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
	ImageType_InvenItem,
	ImageType_NPC,
	ImageType_NPCTextBar,
	ImageType_Item,
	ImageType_DstrObj,
	ImageType_Coin,
	ImageType_Choose_Item,
	ImageType_ItemTextBar,
	ImageType_LikHp,
	ImageType_Dungeon,
	ImageType_MiniWood,
	ImageType_PlayerMini,
	ImageType_Player_MiniChange,
	ImageType_Monster,
	ImageType_QuestMenu,
	ImageType_QuestList,
	ImageType_Treasure_Chest,
	ImageType_Dungeon_Object,
	ImageType_Player_FALL,
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
	BitMap* m_IvenItemBitMap;	    // �κ��丮 ������ �̹��� 
	BitMap* m_FieldBitMap[End_Field];	// �� �̹���
	BitMap* m_NpcBitMap;		//Npc �̹��� 
	BitMap* m_NpcTextBarBitMap; // npc�ؽ�Ʈ�� �̹���
	BitMap* m_ItemBitMap;		// ������ �̹���
	BitMap* m_DstrObjBitMap;		// �ı����ɿ�����Ʈ �̹���
	BitMap* m_CoinBitMap;		// ���� �̹���
	BitMap* m_ChooseItemBitMap;		// ������ ����ǥ�� �̹���
	BitMap* m_ItemTextBarBitMap;
	BitMap* m_LinkHpBitMap;		// ĳ����HP �̹���
	BitMap* m_MiniWoodBitmap;   // �۾��������� ���� ��Ʈ��
	BitMap* m_PlayerMiniBitMap; // �÷��̾� �̴� ��Ʈ��
	BitMap* m_PlayerMiniChangeBitMap; // �÷��̾� ü���� �ִϸ��̼� ��Ʈ��
	BitMap* m_MonsterBitMap;		// ���� ��Ʈ��
	BitMap* m_QuestMenuBitMap;		//����Ʈ �޴� ��Ʈ��
	BitMap* m_QuestListBitMap;		// �پ��� ����Ʈ ��Ʈ��
	BitMap* m_TreasureChestBitmap; // �������� ��Ʈ�� 
	BitMap* m_DungeonObjectBitmap;  // ����������Ʈ��Ʈ��
	BitMap* m_PlayerFallBitmap;		// �÷��̾� �߶� �ִϸ��̼� ��Ʈ��


	PlayerDirBitmap playerDirBitmap;	    // �÷��̾� ���⺰�̹���
	PlayerDirBitmap playerSkillDirBitmap;  // �÷��̾� ���⺰�̹���
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
	PlayerDirBitmap GetPlayerDirBitmap(bool Skill = 0) const 
	{
		if(Skill) 
			return playerSkillDirBitmap;
		else 
			return playerDirBitmap;
	}

	BitMap* GetBackGroundBitMap(FieldType Image) const {
		return m_FieldBitMap[Image];
	}

	void ChangeFont_TextDraw(HDC backDC, std::string str, int FontSize, int x, int y);

};

