#include "BitMap.h"

void BitMap::Init(HDC hdc, char* FileName)
{
	m_memdc = CreateCompatibleDC(hdc); // �޸� DC ����
	m_Bitmap = (HBITMAP)LoadImageA(NULL, FileName, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE); // ���� ��ο��� ��Ʈ�� �ε�
	SelectObject(m_memdc, m_Bitmap); 

	BITMAP BitMap_info; // ��Ʈ�� ũ�� �� ������ ����
	GetObject(m_Bitmap, sizeof(BitMap_info), &BitMap_info);
	m_Size.cy = BitMap_info.bmHeight;
	m_Size.cx = BitMap_info.bmWidth;
}
	

void BitMap::Draw(HDC backDC, int x, int y, bool isAlpha)
{
	switch (isAlpha) /// �������� �����Ұ��� ����
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
