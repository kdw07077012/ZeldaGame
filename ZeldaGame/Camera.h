#pragma once
#include <Windows.h>
#include "Object.h"
class Camera
{
private:
	static Camera* m_hThis; // ½Ì±ÛÅæ »ç¿ë 

public:
	Camera();
	~Camera();

	void Init(int x, int y);
	void Update();

	int GetX() const { return m_posX; }
	int GetY() const { return m_posY; }

	static Camera* GetInstance()
	{
		if (NULL == m_hThis)
			m_hThis = new Camera;

		return m_hThis;
	}

private:
	int m_posX;
	int m_posY;
	int m_speed;
	int m_width;
	int m_height;
};

