#pragma once
#include "BitMap.h"
#include <string>
enum ImageType // 이미지 타입을 통해 불러옴
{
	ImageType_Interface,
	ImageType_BackGround,
	ImageType_Player,
	ImageType_Menu,
	ImageType_InGame
};

class BitMapManager
{
private:
	static BitMapManager* m_hThis; // 싱글톤 사용 

	BitMap m_WindowBitMap;
	BitMap test;
	BitMap* m_BackBitMap; // 배경 이미지
	BitMap* m_PlayerBitMap; // 플레이어 이미지
	BitMap* m_InterfaceBitMap; //인터페이스 UI 이미지
	BitMap* m_MenuBitMap;	   // 메뉴 이미지
	BitMap* m_InGameBitMap;		//인게임 이미지

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

};

