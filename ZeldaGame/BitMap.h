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
	// �ڸ������ϴ� ��Ʈ���� ��ġ, ũ�� 
	void CutDraw(HDC backDC, int x, int y, int CposX, int CposY, SIZE CSize); 
	void BackGroundDraw(HDC backDC, int x, int y);

	~BitMap(); // ��Ʈ�� �޸� ����
};

