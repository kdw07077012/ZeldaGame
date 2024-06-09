#include "Camera.h"
#include "GameManager.h"
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
	m_width = 1500;
	m_height = 1024;
	fTime = 0.0f;
	bMapEndX = false;
}

void Camera::Update(float DeltaTime)
{
	SIZE msize = BitMapManager::GetInstance()->GetWindowSize();
	fTime += DeltaTime;

	// 나중에 필드 맵 크기를 받아와서 필드별로 처리하기 
	if (fTime > 0.01f)
	{
		if (GetAsyncKeyState(0x57) & 0x8000) //W
		{
			if(m_posY <= 0)
				bMapEndY = true;
			else
			{
				bMapEndY = false;
				m_posY -= 500 * DeltaTime;
			}


			
		}
		else if (GetAsyncKeyState(0x41) & 0x8000) // A
		{
			if (m_posX < 0)
				bMapEndX = true;
			else
			{
				bMapEndX = false;
				m_posX -= 500 * DeltaTime;
			}


		}
		else if (GetAsyncKeyState(0x53) & 0x8000) // S
		{


			if (m_posY > m_height - msize.cy)
				bMapEndY = true;
			else
			{
				bMapEndY = false;
				m_posY += 500 * DeltaTime;
			}


		}		
		else if (GetAsyncKeyState(0x44) & 0x8000) // D
		{


			if (m_posX >= m_width - msize.cx)
				bMapEndX = true;
			else
			{
				bMapEndX = false;
				m_posX += 500 * DeltaTime;
			}


		}
		

		

		

		

		fTime = 0.0f;
	}

	

	//std::string integerVal = std::to_string(m_posY);
	////메세지로 출력
	//MessageBoxA(NULL, integerVal.c_str(), NULL, MB_OK);
}
