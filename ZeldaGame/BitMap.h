#pragma once
#include <Windows.h>
class BitMap
{
private:
	HDC m_memdc;		// �⺻ HDC		
	HBITMAP m_Bitmap;	// ��Ʈ��
	SIZE m_Size;		// ��Ʈ�� ������

public:
	SIZE GetSize() const { return m_Size; }  
	void Init(HDC hdc, char* FileName);					// ���Ϻҷ��ͼ� ����
	void Draw(HDC backDC, int x, int y, bool isAlpha); // ��Ʈ�� Draw
	// �ڸ������ϴ� ��Ʈ���� ��ġ, ũ��, Ȯ��������
	void CutDraw(HDC backDC, int x, int y, int CposX, int CposY, SIZE CSize, float fDrainage = 1.0f);
	void BackGroundDraw(HDC backDC, int x, int y, bool isAlpha = 0);
	void AnimationUpdate(HDC backDC, int frame, int x, int y, SIZE size, float fDrainage, int yOffset = 0);
	~BitMap(); // ��Ʈ�� �޸� ����
};

//