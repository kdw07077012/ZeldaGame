#include "GameManager.h"

GameManager* GameManager::m_pThis = NULL;

HBITMAP GameManager::CreateDIBSectionRe(int width, int Height)
{
	BITMAPINFO bm_info;
	ZeroMemory(&bm_info.bmiHeader, sizeof(BITMAPINFOHEADER));
	bm_info.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bm_info.bmiHeader.biBitCount = 24;
	bm_info.bmiHeader.biWidth = width; // 너비.
	bm_info.bmiHeader.biHeight = Height;// 높이.
	bm_info.bmiHeader.biPlanes = 1;

	LPVOID pBits;
	return CreateDIBSection(m_hDC, &bm_info, DIB_RGB_COLORS, (void**)&pBits, NULL, 0);
}

void GameManager::Init(HWND hWnd)
{
	m_hWnd = hWnd;
	m_hDC = GetDC(hWnd);
	backDC = CreateCompatibleDC(m_hDC);

	BitMapManager::GetInstance()->Init(m_hDC);
	WindowSize = BitMapManager::GetInstance()->GetWindowSize();
	m_eCurGameState = GAMESTATE_MENU;

}

void GameManager::Update(float DeltaTime)
{
	
}

void GameManager::DoubleBuffer(float DeltaTime)
{
	RECT windowRect; // 멤버 변수.
	GetWindowRect(m_hWnd, &windowRect); // init 함수에서 호출.

	HBITMAP backBitmap = CreateDIBSectionRe(windowRect.right - windowRect.left, windowRect.bottom - windowRect.top);
	HBITMAP oldBack = (HBITMAP)SelectObject(backDC, backBitmap);

	switch (m_eCurGameState)
	{
	case GAMESTATE_MENU:
		break;
	case GAMESTATE_START:
		break;
	default:
		break;
	}

	BitBlt(m_hDC, 0, 0, windowRect.right - windowRect.left, windowRect.bottom - windowRect.top, backDC, 0, 0, SRCCOPY);
	SelectObject(backDC, oldBack);
	DeleteObject(backBitmap);
}

void GameManager::Release(HWND hWnd)
{
	DeleteObject(backDC);
	ReleaseDC(hWnd, m_hDC);
}
