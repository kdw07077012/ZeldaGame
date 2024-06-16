#pragma once
#include "BitMap.h"
#include <string>

#define WINDOWSIZE_WIDTH 720
#define WINDOWSIZE_HEIGHT 540

//#define DEBUG // 콜리전 텍스트딩 디버깅 
enum ImageType // 이미지 타입을 통해 불러옴
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
	FieldType_Default,  // 기본스타트 맵
	FieldType_Store,    // 상점 맵 
	FieldType_Store_ShoeStroe, // 상점 맵 안 신발 상점
	FieldType_Store_StoreRoom, // 상점 맵 안 스토어 
	FieldType_Dungeon,
	FieldType_Boss,
	End_Field,
};

struct PlayerDirBitmap // 플레이어 방향별 애니메이션을 담을 구조체
{
	BitMap* Left_Bitmap;
	BitMap* Right_Bitmap;
	BitMap* Up_Bitmap;
	BitMap* Down_Bitmap;
};


class BitMapManager
{
private:
	static BitMapManager* m_hThis; // 싱글톤 사용 

	BitMap m_WindowBitMap;

	BitMap* m_ButtonBitMap;		// 버튼 이미지
	BitMap* m_TitleBitMap;		// 타이틀 이미지
	BitMap* m_BackBitMap;		// 배경 이미지
	BitMap* m_InterfaceBitMap;  //인터페이스 UI 이미지
	BitMap* m_MenuBitMap;	    // 메뉴 이미지
	BitMap* m_InGameBitMap;		//인게임 이미지
	BitMap* m_PlayerHudBitMap;  // HUD 이미지  
	BitMap* m_InventoryBitMap;  // HUD 이미지  
	BitMap* m_IvenItemBitMap;	    // 인벤토리 아이템 이미지 
	BitMap* m_FieldBitMap[End_Field];	// 맵 이미지
	BitMap* m_NpcBitMap;		//Npc 이미지 
	BitMap* m_NpcTextBarBitMap; // npc텍스트바 이미지
	BitMap* m_ItemBitMap;		// 아이템 이미지
	BitMap* m_DstrObjBitMap;		// 파괴가능오브젝트 이미지
	BitMap* m_CoinBitMap;		// 코인 이미지
	BitMap* m_ChooseItemBitMap;		// 아이템 선택표시 이미지
	BitMap* m_ItemTextBarBitMap;
	BitMap* m_LinkHpBitMap;		// 캐릭터HP 이미지
	BitMap* m_MiniWoodBitmap;   // 작아지기위한 나무 비트맵
	BitMap* m_PlayerMiniBitMap; // 플레이어 미니 비트맵
	BitMap* m_PlayerMiniChangeBitMap; // 플레이어 체인지 애니메이션 비트맵
	BitMap* m_MonsterBitMap;		// 몬스터 비트맵
	BitMap* m_QuestMenuBitMap;		//퀘스트 메뉴 비트맵
	BitMap* m_QuestListBitMap;		// 다양한 퀘스트 비트맵
	BitMap* m_TreasureChestBitmap; // 보물상자 비트맵 
	BitMap* m_DungeonObjectBitmap;  // 던전오브젝트비트맵
	BitMap* m_PlayerFallBitmap;		// 플레이어 추락 애니메이션 비트맵


	PlayerDirBitmap playerDirBitmap;	    // 플레이어 방향별이미지
	PlayerDirBitmap playerSkillDirBitmap;  // 플레이어 방향별이미지
public:
	static BitMapManager* GetInstance() // 싱글톤
	{
		if (m_hThis == NULL)
			m_hThis = new BitMapManager;

		return m_hThis;
	}

	void Init(HDC hdc);

	BitMap* ImageRoad(HDC hdc, const char* FileName, ImageType type); // 타입의 이미지 로드
	BitMap* GetBitMap(ImageType Image) const; 					 // 해당 타입의 이미지 반환
	SIZE GetWindowSize() const { return m_WindowBitMap.GetSize(); }  // 윈도우 사이즈 반환
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

