#include "Inventory.h"
#include "GameManager.h"
Inventory::Inventory()
{
	m_BitMap = BitMapManager::GetInstance()->GetBitMap(ImageType_Inventory);
	
	int Count = 0;
	Enabled = false;
	SelectItem = NULL;

	for (int i = 0; i < 3; i++) // 세로
	{
		for (int j = 0; j < 4; j++) // 가로 
		{
			SlotPos[Count].X = SLOT_STARTX + (SLOT_OFFEST_X * j + 1);
			SlotPos[Count].Y = SLOT_STARTY + (SLOT_OFFEST_Y * i + 1);
			Count++;

			ItemSlot* itemSlot = new ItemSlot;
			
			itemSlot->pos.X = SLOT_STARTX + (SLOT_OFFEST_X * j + 1);
			itemSlot->pos.Y = SLOT_STARTY + (SLOT_OFFEST_Y * i + 1);
			itemSlots.push_back(itemSlot);
		}

		
	}



	Item* item = new Item(Item_Sword, 0, 0, ItemImageType_Inven);
	AddItem(item);

}
//ImageType_InvenItem

Inventory::~Inventory()
{

}

void Inventory::Draw(HDC backDC, float DeltaTime)
{
	m_BitMap->Draw(backDC, 0, 0, 0);

	for (ItemSlot* slot : itemSlots)
	{
		slot->Draw(backDC, DeltaTime);
	}

	//item->Draw(backDC, DeltaTime);
	//item->PosUpdate(SlotPos[0].X, SlotPos[0].Y);
}

void Inventory::Update(float DeltaTime, POINT mousePos)
{
	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) // 키 눌렀는지
	{
		
		for (ItemSlot* slot : itemSlots) // 인벤선택 체크 
		{
			if (slot->pos.X < mousePos.x && slot->pos.X + SLOT_SIZEX > mousePos.x)
			{
				if (slot->pos.Y < mousePos.y && slot->pos.Y + SLOT_SIZEY > mousePos.y)
				{
					if (SelectItem != NULL)
					{
						SelectItem->Selected = false;
					}

					slot->Selected = true;
					SelectItem = slot;
					break;
				}
			}
		}

	}







	
}

bool Inventory::AddItem(Item* _item)
{
	for (ItemSlot* slot : itemSlots)
	{
		if (slot->GetItem() == NULL)
		{
			_item->itemPos = slot->pos;
			slot->SlotItemAdd(_item);
			return true;
		}
	}

	return false;
}

void Inventory::Reset()
{
}
