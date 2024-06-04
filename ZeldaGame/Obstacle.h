#pragma once
#include <Windows.h>

class Obstacle
{
protected:
	int m_left;
	int m_Top;
	int m_Right;
	int m_Bottom;
	RECT m_RectCollision; // ÄÝ¸®Àü
public:
	Obstacle();
	void Init(int _left, int _Top, int _Right, int _Bottom);
    void Draw(HDC backDC, int cameraX, int CameraY);
	RECT& GetCollision() { return m_RectCollision; }


};

