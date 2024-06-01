#pragma once
#include "BitMap.h"

#include <string>
enum ImageType // 이미지 타입을 통해 불러옴
{
	ImageType_Title,
	ImageType_Interface,
	ImageType_BackGround,
	ImageType_Player,
	ImageType_Menu,
	ImageType_InGame,
	ImageType_Button,
	ImageType_HUD,
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

	PlayerDirBitmap playerDirBitmap;	    // 플레이어 방향별이미지

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
	PlayerDirBitmap GetPlayerDirBitmap() const { return playerDirBitmap; }

};

