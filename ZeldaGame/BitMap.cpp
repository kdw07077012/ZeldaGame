#include "BitMap.h"

void BitMap::Init(HDC hdc, char* FileName)
{
	m_memdc = CreateCompatibleDC(hdc);
	m_Bitmap = (HBITMAP)LoadImageA(NULL, FileName, IMAGE_BITMAP, 0, 0,
		LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);
	SelectObject(m_memdc, m_Bitmap);

	BITMAP BitMap_info;
	GetObject(m_Bitmap, sizeof(BitMap_info), &BitMap_info);
	m_Size.cx = BitMap_info.bmWidth;
	m_Size.cy = BitMap_info.bmHeight;
}
	

void BitMap::Draw(HDC backDC, int x, int y, bool isAlpha)
{
	switch (isAlpha) /// 바탕색을 제거할건지 선택
	{
	case 1:
		TransparentBlt(backDC, x, y, m_Size.cx, m_Size.cy, m_memdc, 0, 0, m_Size.cx, m_Size.cy, RGB(244, 0, 244));
		break;
	case 0:
		BitBlt(backDC, x, y, m_Size.cx, m_Size.cy, m_memdc, 0, 0, SRCCOPY);
		break;
	}
}

void BitMap::CutDraw(HDC backDC, int x, int y, int CposX, int CposY, SIZE CSize)
{
	TransparentBlt(backDC, x, y, m_Size.cx, m_Size.cy, m_memdc, CposX, CposY, CSize.cx, CSize.cy, RGB(244, 0, 244));
}

void BitMap::BackGroundDraw(HDC backDC, int x, int y)
{
	BitBlt(backDC, 0, 0, m_Size.cx, m_Size.cy, m_memdc, x, y, SRCCOPY);
}

BitMap::~BitMap()
{
	DeleteObject(m_Bitmap);
	DeleteDC(m_memdc);
}
