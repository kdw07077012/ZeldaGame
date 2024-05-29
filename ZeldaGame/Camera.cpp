#include "Camera.h"

Camera* Camera::m_hThis = NULL;

Camera::Camera()
{
}

Camera::~Camera()
{
}

void Camera::Init(int x, int y)
{
	m_posX = x;
	m_posY = y;
}

void Camera::Update()
{
	SIZE msize = BitMapManager::GetInstance()->GetWindowSize();


	if (GetAsyncKeyState(0x57) & 0x8000 && m_posY > 0) //W
	{
		m_posY -= 5;
	}

	if (GetAsyncKeyState(0x53) & 0x8000 && m_posY < 1024 - msize.cy) // S
	{
		m_posY += 5;
	}

	if (GetAsyncKeyState(0x41) & 0x8000 && m_posX > 0) // A
	{
		m_posX -= 5;
	}

	if (GetAsyncKeyState(0x44) & 0x8000 && m_posX < 1500 - msize.cx) // D
	{

		m_posX += 5;
	}

	//std::string integerVal = std::to_string(m_posY);
	////메세지로 출력
	//MessageBoxA(NULL, integerVal.c_str(), NULL, MB_OK);
}
