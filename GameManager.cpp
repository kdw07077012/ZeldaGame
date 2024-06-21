#include "GameManager.h"
#
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
	m_eCurGameState = GAMESTATE_TITLE;
	Camera::GetInstance()->Init(0,0);
	currentField = FieldType_Default;

	//�����Ҵ�
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

	//�ٿ�ĳ����,
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
	
	// �޸� ������ ���� ������Ʈ ����Ʈ�� ���� : �Ѳ����� �����Ҵ� ���� 
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

		if (GetAsyncKeyState(0x51) && 0x8000) // ����Ʈ ���� �ݱ� IŰ
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
	
	NPC* temp = NULL; // �ʵ� NPC üũ�ϱ� ���� ���� ������

	switch (m_eCurGameState) //�ʵ庰 ������Ʈ
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

		if (m_Player->PlayerInput(DeltaTime)) // ĳ���Ͱ� ������ ���ִ����� ���� ī�޶� ����
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
				if (GetAsyncKeyState(VK_RETURN) & 0x8000) // Enter ����Ʈ ����
				{

					Quest* quest = m_QuestSystem->FindQuest(temp->GetQuest()->GetQuestType());


					if (quest != NULL)
					{
						quest->CompleateCheck(); // ����Ʈ Ȯ�� Ŭ���� üũ

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
				if (GetAsyncKeyState(VK_RETURN) & 0x8000) // Enter ����Ʈ ����
				{
					// ���� ����Ʈ�� �ߺ� ����Ʈ�� ������
					Quest* quest = m_QuestSystem->FindQuest(temp->GetQuest()->GetQuestType());


					if (quest != NULL)
					{
						quest->CompleateCheck(); // ����Ʈ Ȯ�� Ŭ���� üũ
						Quest_OnNotify(QuestType_ShoeHelp); // �Ź߰��� �����ִ� ����Ʈ �Ϸ� �˸� 
	
					}
					else
					{
						Quest_Add(temp->GetQuest());
					}
					//����Ʈ ����


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


		if (GetAsyncKeyState(0x45) && 0x8000) //E ���� , ������ ����
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
			if (GetAsyncKeyState(VK_RETURN) & 0x8000) // Ű ���õȻ��¿��� ���ʹ����� ��� ����
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
	RECT windowRect; // ��� ����.
	GetWindowRect(m_hWnd, &windowRect); // init �Լ����� ȣ��.

	HBITMAP backBitmap = CreateDIBSectionRe(windowRect.right - windowRect.left, windowRect.bottom - windowRect.top);

	HBITMAP oldBack = (HBITMAP)SelectObject(backDC, backBitmap);


	// ������ �׷��ֱ����� ���
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

		// �÷��̾� ���� ��� ǥ��
		BitMapManager::GetInstance()->ChangeFont_TextDraw(backDC, std::to_string(m_Player->GetCurrentCoin()), 20, 270, 15); 
		if (currentField == FieldType_Store)
			m_StoreField->BackDraw(backDC, DeltaTime);
		else if (currentField == FieldType_Dungeon)
			m_Dungeon_Field->BackDraw(backDC, DeltaTime);	
		else if(currentField == FieldType_Ending)
			m_EndingField->BackDraw(backDC, DeltaTime);


		m_HUD->Draw(backDC, DeltaTime);						  // HUD ǥ��
		m_QuestSystem->QuestComplete_Draw(backDC, DeltaTime); // ����Ʈ ���ø�Ʈ�� ǥ��
		
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
	BitMapManager::GetInstance()->Release(); // �޸� ��ü

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
			// �ٷ� ü������
			break;
		case InGame_Item_Position:
			m_Player->Hp_Portion();
			// �ٷ� ȸ��
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
		// �ٷ� ü������
		break;
	case InGame_Item_Position:
		m_Player->Hp_Portion();
		// �ٷ� ȸ��
		break;
	default:
		break;
	}
}

void GameManager::Quest_OnNotify(QuestType type)
{
	m_QuestSystem->Notify(type);  // ����Ʈ Ÿ�Կ� �°� ȣ��
}

void GameManager::Quest_Add(Quest* quest)
{
	m_QuestSystem->AddObserver(quest);  // ����Ʈ �߰� 
}
