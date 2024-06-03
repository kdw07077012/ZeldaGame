#include "Obstacle.h"

Obstacle::Obstacle()
{
}

void Obstacle::Init(int _left, int _Top, int _Right, int _Bottom)
{
	m_left = _left;
	m_Top = _Top;
	m_Right = _Right;
	m_Bottom = _Bottom;
	m_RectCollision = { _left, _Top, _Right, _Bottom };
}

void Obstacle::Draw(HDC backDC, int cameraX, int CameraY)
{
	m_RectCollision = { m_left - cameraX, m_Top - CameraY, m_Right - cameraX, m_Bottom - CameraY };

#ifdef DEBUG
	Rectangle(backDC, m_left - cameraX, m_Top - CameraY, m_Right - cameraX, m_Bottom - CameraY);
#endif // DEBUG
	
		
}

