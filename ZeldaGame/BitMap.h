#pragma once
#include <Windows.h>
class BitMap
{
private:
	HDC m_memdc;		// 기본 HDC		
	HBITMAP m_Bitmap;	// 비트맵
	SIZE m_Size;		// 비트맵 사이즈

public:
	SIZE GetSize() const { return m_Size; }  
	void Init(HDC hdc, char* FileName);					// 파일불러와서 생성
	void Draw(HDC backDC, int x, int y, bool isAlpha); // 비트맵 Draw

	~BitMap(); // 비트맵 메모리 해제
};

