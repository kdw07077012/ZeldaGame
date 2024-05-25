#include "BitMap.h"

void BitMap::Init(HDC hdc, char* FileName)
{
	m_memdc = CreateCompatibleDC(hdc); // 메모리 DC 생성
	m_Bitmap = (HBITMAP)LoadImageA(NULL, FileName, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE); // 파일 경로에서 비트맵 로드
	SelectObject(m_memdc, m_Bitmap); 

	BITMAP BitMap_info; // 비트맵 크기 등 정보를 담음
	GetObject(m_Bitmap, sizeof(BitMap_info), &BitMap_info);
	m_Size.cy = BitMap_info.bmHeight;
	m_Size.cx = BitMap_info.bmWidth;
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

BitMap::~BitMap()
{
	DeleteObject(m_Bitmap);
	DeleteDC(m_memdc);
}
