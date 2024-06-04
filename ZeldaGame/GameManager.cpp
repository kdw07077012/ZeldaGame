#include "GameManager.h"

GameManager* GameManager::m_pThis = NULL;

HBITMAP GameManager::CreateDIBSectionRe(int width, int Height)
{
	BITMAPINFO bm_info;
	ZeroMemory(&bm_info.bmiHeader, sizeof(BITMAPINFOHEADER));
	bm_info.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bm_info.bmiHeader.biBitCount = 24;
	bm_info.bmiHeader.biWidth = width; // �ʺ�.
	bm_info.bmiHeader.biHeight = Height;// ����.
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
	m_eCurGameState = GAMESTATE_START;
	Camera::GetInstance()->Init(0,0);
	currentField = FieldType_Default;

	//�����Ҵ�
	m_Menu = new Menu;
	m_Title = new Title;
	m_BackGround = new BackGround(Default_Field);
	m_Player = new Player;
	m_Field = new Field;
	m_HUD = new HUD;
	m_Ivnentory = new Inventory;
	m_StoreField = new Store_Field;
	m_ShoeStroe_Field = new ShoeStroe_Field;
	m_StoreRoom_Field = new StoreRoom_Field;
	m_Npc = new NPC;

	//�ٿ�ĳ����,
	m_oMenu = dynamic_cast<Object*>(m_Menu);
	m_oTitle = dynamic_cast<Object*>(m_Title);
	m_oBackGround = dynamic_cast<Object*>(m_BackGround);
	m_oPlayer = dynamic_cast<Object*>(m_Player);

	Camera::GetInstance()->Init(650, 370); // 613 370
}

void GameManager::Update(float DeltaTime)
{
	if (m_eCurGameState == GAMESTATE_START || m_eCurGameState == GAMESTATE_INVENTORY)
	{
		if (GetAsyncKeyState(0x49) && 0x8000) // �κ��丮 ���� �ݱ� IŰ
		{
			if (m_Ivnentory->Enabled == false)
			{
				m_Ivnentory->Enabled = true;
				m_eCurGameState = GAMESTATE_INVENTORY;
			}
			else
			{
				m_Ivnentory->Enabled = false;
				m_eCurGameState = GAMESTATE_START;
			}
			
		}
	}
	
	


	switch (m_eCurGameState)
	{
	case GAMESTATE_TITLE:
		m_Title->Update(DeltaTime);
		if (m_Title->GetGameState())
		{
			m_eCurGameState = GAMESTATE_MENU;
		}
		break;
	case GAMESTATE_MENU:
		GetCursorPos(&ptMouse);
		ScreenToClient(m_hWnd, &ptMouse);		
		m_Menu->MenuSelect(ptMouse);

		if (GetAsyncKeyState(VK_LBUTTON) & 0x8000 && m_Menu->m_bEnableButton)
		{
			//std::string integerVal = std::to_string(0);
			// �޼����� ���
			//MessageBoxA(NULL, integerVal.c_str(), NULL, MB_OK);

			switch (m_Menu->m_currSelectMenu)
			{
			case SelectMenu_START:
				m_eCurGameState = GAMESTATE_START;
				break;
			case SelectMenu_EDIT:
				break;
			case SelectMenu_QUIT:
				break;
			}
		}

		break;
	case GAMESTATE_START:

		if (m_Player->PlayerInput(DeltaTime)) // ĳ���Ͱ� ������ ���ִ����� ���� ī�޶� ����
		{
			Camera::GetInstance()->Update(DeltaTime);
		}
		
		m_Player->Update(DeltaTime);
		m_BackGround->Update(DeltaTime);
		

		
		
		break;
	case GAMESTATE_INVENTORY:
	

		GetCursorPos(&ptMouse);
		ScreenToClient(m_hWnd, &ptMouse);
		m_Ivnentory->Update(DeltaTime, ptMouse);
		
			
		
		break;
	default:
		break;
	}
}

void GameManager::DoubleBuffer(float DeltaTime)
{
	RECT windowRect; // ��� ����.
	GetWindowRect(m_hWnd, &windowRect); // init �Լ����� ȣ��.

	HBITMAP backBitmap = CreateDIBSectionRe(windowRect.right - windowRect.left, windowRect.bottom - windowRect.top);

	HBITMAP oldBack = (HBITMAP)SelectObject(backDC, backBitmap);

	switch (m_eCurGameState)
	{
	case GAMESTATE_TITLE:
		m_Title->Draw(backDC, DeltaTime);
		break;
	case GAMESTATE_MENU:
		m_Menu->Draw(backDC, DeltaTime);
		break;
	case GAMESTATE_START:	
		
		switch (currentField)
		{
		case FieldType_Default:
			m_Field->Draw(backDC, DeltaTime);
			m_Npc->Draw(backDC, DeltaTime);
			break;
		case FieldType_Store:
			m_StoreField->Draw(backDC, DeltaTime);
			break;
		case FieldType_Store_ShoeStroe:
			m_ShoeStroe_Field->Draw(backDC, DeltaTime);
			break;
		case FieldType_Store_StoreRoom:
			m_StoreRoom_Field->Draw(backDC, DeltaTime);
			break;
		case FieldType_Dungeon:
			break;
		case FieldType_Boss: 
			break;
		case End_Field:
			break;
		default:
			break;
		}


		
		

		m_Player->Draw(backDC, DeltaTime);	
		m_Field->Draw(backDC, DeltaTime);
		m_HUD->Draw(backDC, DeltaTime);
		
		break;
	case GAMESTATE_INVENTORY:
		m_Ivnentory->Draw(backDC, DeltaTime);
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

bool GameManager::FieldCollision(RECT rect)
{
	switch (currentField)
	{
	case FieldType_Default:
		if (m_Field->Collision(rect))
			return true;
		break;
	case FieldType_Store:
		if (m_StoreField->Collision(rect))
			return true;
		break;
	case FieldType_Store_ShoeStroe:
		if (m_ShoeStroe_Field->Collision(rect))
			return true;
		break;
	case FieldType_Store_StoreRoom:
		if (m_StoreRoom_Field->Collision(rect))
			return true;
		break;
	case FieldType_Dungeon:
		break;
	case FieldType_Boss:
		break;
	case End_Field:
		break;
	default:
		break;
	}
	
	return false;
}

void GameManager::NextField(FieldType Field)
{
	currentField = FieldType(Field);

	switch (Field)
	{
	case FieldType_Default:
		break;
	case FieldType_Store:
		m_StoreField->Init();
		break;
	case FieldType_Store_ShoeStroe:
		m_ShoeStroe_Field->Init();
		break;
	case FieldType_Store_StoreRoom:
		m_StoreRoom_Field->Init();
		break;
	case FieldType_Dungeon:
		break;
	case FieldType_Boss:
		break;
	case End_Field:
		break;
	default:
		break;
	}
}
