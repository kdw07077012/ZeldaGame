#include "GameManager.h"
#
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
	m_eCurGameState = GAMESTATE_TITLE;
	Camera::GetInstance()->Init(0,0);
	currentField = FieldType_Default;

	//동적할당
	m_Menu = new Menu;
	m_Title = new Title;

	m_Player = new Player;
	m_Field = new Field;
	m_HUD = new HUD;
	m_Ivnentory = new Inventory;
	m_StoreField = new Store_Field;
	m_ShoeStroe_Field = new ShoeStroe_Field;
	m_StoreRoom_Field = new StoreRoom_Field;
	m_Dungeon_Field = new Dungeon_Field;
	m_QuestSystem = new QuestSystem;
	m_Boss_Field = new Boss_Field;
	m_EndingField = new Ending_Field;
	m_EndingCredit_Field = new EndingCredit_Field;

	//다운캐스팅,
	m_oMenu			     = dynamic_cast<Object*>(m_Menu);
	m_oTitle		     = dynamic_cast<Object*>(m_Title);
	m_oPlayer		     = dynamic_cast<Object*>(m_Player);
	m_oStoreField        = dynamic_cast<Object*>(m_StoreField);
	m_oShoeField	     = dynamic_cast<Object*>(m_ShoeStroe_Field);
	m_oDungeonField	     = dynamic_cast<Object*>(m_Dungeon_Field);
	m_oBossField         = dynamic_cast<Object*>(m_Boss_Field);
	m_oQuestSystem	     = dynamic_cast<Object*>(m_QuestSystem);
	m_oEndingField       = dynamic_cast<Object*>(m_EndingField);
	m_oEndingCreditField = dynamic_cast<Object*>(m_EndingCredit_Field);
	m_oHUD				 = dynamic_cast<Object*>(m_HUD);
	m_oInventory     	 = dynamic_cast<Object*>(m_Ivnentory);
	
	// 메모리 관리를 위해 오브젝트 리스트에 담음 : 한꺼번에 동정할당 해제 
	objects.push_back(m_oMenu);
	objects.push_back(m_oTitle);
	objects.push_back(m_oPlayer);
	objects.push_back(m_oStoreField);
	objects.push_back(m_oShoeField);
	objects.push_back(m_oDungeonField);
	objects.push_back(m_oBossField);
	objects.push_back(m_oQuestSystem);
	objects.push_back(m_oEndingField);
	objects.push_back(m_oEndingCreditField);
	objects.push_back(m_oHUD);
	objects.push_back(m_oInventory);


	Item* item = new Item(Item_Shield, 0, 0, ItemImageType_Inven);
	m_Ivnentory->AddItem(item);
}

void GameManager::Update(float DeltaTime)
{
	if (m_eCurGameState == GAMESTATE_START || m_eCurGameState == GAMESTATE_INVENTORY || m_eCurGameState == GAMESTATE_QUEST)
	{
		if (GetAsyncKeyState(0x49) && 0x8000) // 인벤토리 열고 닫기 I키
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

		if (GetAsyncKeyState(0x51) && 0x8000) // 퀘스트 열고 닫기 I키
		{
			if (m_QuestSystem->Enabled == false)
			{
				m_QuestSystem->Enabled = true;
				m_eCurGameState = GAMESTATE_QUEST;
			}
			else
			{
				m_QuestSystem->Enabled = false;
				m_eCurGameState = GAMESTATE_START;
			}
			
		}
	}
	
	NPC* temp = NULL; // 필드 NPC 체크하기 위한 담을 포인터

	switch (m_eCurGameState) //필드별 업데이트
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
			// 메세지로 출력
			//MessageBoxA(NULL, integerVal.c_str(), NULL, MB_OK);

			switch (m_Menu->m_currSelectMenu)
			{
			case SelectMenu_START:
				Camera::GetInstance()->Init(650, 370); // 613 370
				GetPlayer()->m_pos = { 650, 370 };
				currentField = FieldType_Default;
				m_eCurGameState = GAMESTATE_START;

				m_Field->Reset();
				m_ShoeStroe_Field->Reset();
			
				m_StoreField->Reset();
				m_Player->Reset();
				m_HUD->Reset();
				m_Ivnentory->Reset();
				break;
			case SelectMenu_QUIT:
				break;
			}
		}

		break;
	case GAMESTATE_START:

		if (m_Player->PlayerInput(DeltaTime)) // 캐릭터가 움직일 수있는지에 따라 카메라 추적
		{
			Camera::GetInstance()->Update(DeltaTime);
		}

		m_Player->Update(DeltaTime);
		
		switch (currentField)
		{
		case FieldType_Default:
			m_Field->Update(DeltaTime);
			temp = m_Field->FieldNpcCollision(GetPlayer()->getCollision());
			if (NULL != temp)
			{
				if (GetAsyncKeyState(VK_RETURN) & 0x8000) // Enter 퀘스트 수락
				{

					Quest* quest = m_QuestSystem->FindQuest(temp->GetQuest()->GetQuestType());


					if (quest != NULL)
					{
						quest->CompleateCheck(); // 퀘스트 확인 클리어 체크

					}
					else
					{
						Quest_Add(temp->GetQuest());
					}

				}

			}
			break;
		case FieldType_Store:
			m_StoreField->Update(DeltaTime);
			break;
		case FieldType_Store_ShoeStroe:
			m_ShoeStroe_Field->Update(DeltaTime);

			temp = m_ShoeStroe_Field->FieldNpcCollision(GetPlayer()->getCollision());
			if (NULL != temp)
			{
				if (GetAsyncKeyState(VK_RETURN) & 0x8000) // Enter 퀘스트 수락
				{
					// 현재 퀘스트가 중복 퀘스트가 없을시
					Quest* quest = m_QuestSystem->FindQuest(temp->GetQuest()->GetQuestType());


					if (quest != NULL)
					{
						quest->CompleateCheck(); // 퀘스트 확인 클리어 체크
						Quest_OnNotify(QuestType_ShoeHelp); // 신발가게 도와주는 퀘스트 완료 알림 
	
					}
					else
					{
						Quest_Add(temp->GetQuest());
					}
					//퀘스트 수락


				}
			}
			break;
		case FieldType_Store_StoreRoom:
			m_StoreRoom_Field->Update(DeltaTime);

			break;
		case FieldType_Dungeon:
			m_Dungeon_Field->Update(DeltaTime);
			m_Dungeon_Field->Collision(m_Player->getCollision());
			break;
		case FieldType_Boss:
			m_Boss_Field->Update(DeltaTime);
			break;
		case FieldType_Ending:
			m_EndingField->Update(DeltaTime);
			break;
		default:
			break;
		}


		if (GetAsyncKeyState(0x45) && 0x8000) //E 변신 , 아이템 구매
		{
			switch (currentField)
			{
			case FieldType_Default:
				m_Field->MiniChangeWood_Collision(m_Player->getCollision());
				break;
			case FieldType_Store_StoreRoom:
				m_StoreRoom_Field->Buy_InputCheck();
				break;

			}

			
			
		}


		break;
	case GAMESTATE_INVENTORY:
	

		GetCursorPos(&ptMouse);
		ScreenToClient(m_hWnd, &ptMouse);
		m_Ivnentory->Update(DeltaTime, ptMouse);
		
		if (m_Ivnentory->SelectItem != NULL)
		{
			if (GetAsyncKeyState(VK_RETURN) & 0x8000) // 키 선택된상태에서 엔터누를시 장비 장착
			{
				if (m_Ivnentory->SelectItem->IvenSlot->ItemEquipment)
				{
					m_Ivnentory->SelectItem->IvenSlot->ItemEquipment = false;
					m_HUD->EquipmentedItem(m_Ivnentory->SelectItem->GetItem()->item, false);
					m_Player->EqupmentAdd(m_Ivnentory->SelectItem->GetItem()->item, false);
				}
				else
				{
					m_Ivnentory->IvenSlotEquipmentCheck();
					m_Ivnentory->SelectItem->IvenSlot->ItemEquipment = true;
					m_HUD->EquipmentedItem(m_Ivnentory->SelectItem->GetItem()->item, true);
					m_Player->EqupmentAdd(m_Ivnentory->SelectItem->GetItem()->item, true);
				}

				
			}
		}
			
		
		break;
	default:
		break;
	}
}

void GameManager::DoubleBuffer(float DeltaTime)
{
	RECT windowRect; // 멤버 변수.
	GetWindowRect(m_hWnd, &windowRect); // init 함수에서 호출.

	HBITMAP backBitmap = CreateDIBSectionRe(windowRect.right - windowRect.left, windowRect.bottom - windowRect.top);

	HBITMAP oldBack = (HBITMAP)SelectObject(backDC, backBitmap);


	// 바탕색 그려주기위해 사용
	HBRUSH brush = CreateSolidBrush(RGB(248, 240, 224));
	RECT rect = { windowRect.left,windowRect.top, windowRect.right, windowRect.bottom };
	FillRect(backDC, &rect, brush);


	
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
			m_Dungeon_Field->Draw(backDC, DeltaTime);
			break;
		case FieldType_Boss: 
			m_Boss_Field->Draw(backDC, DeltaTime);		
			break;
		case FieldType_Ending:
			m_EndingField->Draw(backDC, DeltaTime);
			break;
		default:
			break;
		}

		m_Player->Draw(backDC, DeltaTime);

		// 플레이어 현재 루비 표시
		BitMapManager::GetInstance()->ChangeFont_TextDraw(backDC, std::to_string(m_Player->GetCurrentCoin()), 20, 270, 15); 
		if (currentField == FieldType_Store)
			m_StoreField->BackDraw(backDC, DeltaTime);
		else if (currentField == FieldType_Dungeon)
			m_Dungeon_Field->BackDraw(backDC, DeltaTime);	
		else if(currentField == FieldType_Ending)
			m_EndingField->BackDraw(backDC, DeltaTime);


		m_HUD->Draw(backDC, DeltaTime);						  // HUD 표시
		m_QuestSystem->QuestComplete_Draw(backDC, DeltaTime); // 퀘스트 컴플리트시 표시
		
		break;
	case GAMESTATE_INVENTORY:
		m_Ivnentory->Draw(backDC, DeltaTime);

		break;
	case GAMESTATE_QUEST:
		m_QuestSystem->Draw(backDC, DeltaTime);
		break;
	case GAMESTATE_Credit:
		m_EndingCredit_Field->Draw(backDC, DeltaTime);
		break;
	default:
		break;
	}
	



	BitBlt(m_hDC, 0, 0, windowRect.right - windowRect.left, windowRect.bottom - windowRect.top, backDC, 0, 0, SRCCOPY);
	
	SelectObject(backDC, oldBack);
	DeleteObject(backBitmap);
	DeleteObject(brush);

}

void GameManager::Release(HWND hWnd)
{
	for (Object* object : objects)
	{
		free(object);
	}

	objects.clear();
	BitMapManager::GetInstance()->Release(); // 메모리 해체

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
		if (m_Dungeon_Field->Collision(rect))
			return true;
		break;
	case FieldType_Boss:
		if (m_Boss_Field->Collision(rect))
			return true;
		break;
	case FieldType_Ending:
		m_EndingField->Collision(rect);
		break;
	default:
		break;
	}
	
	return false;
}

bool GameManager::FieldObject_AttackCollision(RECT rect)
{
	dstrObj* obj = NULL;

	switch (currentField)
	{
	case FieldType_Default:
		obj = m_Field->AttackableObjects_Collision(rect);
		if (obj != NULL)
		{
			obj->AttackedObject();
			return true;
		}

		m_Field->Monsters_Collision(rect);
			
		break;
	case FieldType_Store:
		break;
	case FieldType_Store_ShoeStroe:
		break;
	case FieldType_Store_StoreRoom:
		break;
	case FieldType_Dungeon:

		m_Dungeon_Field->Monsters_Collision(rect);
		break;
	case FieldType_Boss:
		m_Boss_Field->Boss_Collision(rect);
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
		m_Field->Init();
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
		m_Dungeon_Field->Init();
		break;
	case FieldType_Boss:
		m_Boss_Field->Init();
		break;
	case FieldType_Ending:
		m_EndingField->Init();
		break;
	case FieldType_ending_credits:
		m_eCurGameState = GAMESTATE_Credit;
		break;
	default:
		break;
	}
}

void GameManager::StoreItemBuy(InGame_Item itemType, int price)
{
	if (m_Player->GetCurrentCoin() >= price)
	{
		Item* item;

		switch (itemType)
		{
		case InGame_Item_Lanton:
			item = new Item(Item_Lanton, 0, 0, ItemImageType_Inven);
			m_Ivnentory->AddItem(item);
			break;
		case InGame_Item_Shield:
			item = new Item(Item_Shield, 0, 0, ItemImageType_Inven);
			m_Ivnentory->AddItem(item);
			break;
		case InGame_Item_HpAdd:
			m_Player->AddMaxHP();
			m_HUD->HPMaxAdd();
			// 바로 체력증가
			break;
		case InGame_Item_Position:
			m_Player->Hp_Portion();
			// 바로 회복
			break;
		default:
			break;
		}

		m_Player->RemvoeCoin(price);
	}
}

void GameManager::useItem(InGame_Item itemType)
{
	switch (itemType)
	{
	case InGame_Item_HpAdd:
		m_Player->AddMaxHP();
		m_HUD->HPMaxAdd();
		// 바로 체력증가
		break;
	case InGame_Item_Position:
		m_Player->Hp_Portion();
		// 바로 회복
		break;
	default:
		break;
	}
}

void GameManager::Quest_OnNotify(QuestType type)
{
	m_QuestSystem->Notify(type);  // 퀘스트 타입에 맞게 호출
}

void GameManager::Quest_Add(Quest* quest)
{
	m_QuestSystem->AddObserver(quest);  // 퀘스트 추가 
}
