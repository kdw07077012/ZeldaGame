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
	// 자르고자하는 비트맵의 위치, 크기, 확대배수설정
	void CutDraw(HDC backDC, int x, int y, int CposX, int CposY, SIZE CSize, float fDrainage = 1.0f);
	void BackGroundDraw(HDC backDC, int x, int y, bool isAlpha = 0);
	void AnimationUpdate(HDC backDC, int frame, int x, int y, SIZE size, float fDrainage, int yOffset = 0);
	~BitMap(); // 비트맵 메모리 해제
};

//