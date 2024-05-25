#pragma once
#include "BitMap.h"
#include <string>
enum ImageType // �̹��� Ÿ���� ���� �ҷ���
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
	static BitMapManager* m_hThis; // �̱��� ��� 

	BitMap m_WindowBitMap;
	BitMap test;
	BitMap* m_BackBitMap; // ��� �̹���
	BitMap* m_PlayerBitMap; // �÷��̾� �̹���
	BitMap* m_InterfaceBitMap; //�������̽� UI �̹���
	BitMap* m_MenuBitMap;	   // �޴� �̹���
	BitMap* m_InGameBitMap;		//�ΰ��� �̹���

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

};

