#include "Inventory.h"

Inventory::Inventory()
{
	m_BitMap = BitMapManager::GetInstance()->GetBitMap(ImageType_Inventory);
	int Count = 0;
	Enabled = false;

	for (int i = 0; i < 3; i++) // ����
	{
		for (int j = 0; j < 4; j++) // ���� 
		{
			SlotPos[Count].X = SLOT_STARTX + (110 * j + 1);
			SlotPos[Count].Y = SLOT_STARTY + (78 * i + 1);  
			Count++;

			ItemSlot* itemSlot = new ItemSlot;
			itemSlot->item = NULL;
			itemSlot->pos.X = SLOT_STARTX + (110 * j + 1);
			itemSlot->pos.Y = SLOT_STARTY + (78 * i + 1);
			itemSlots.push_back(itemSlot);
		}

		
	}


}

Inventory::~Inventory()
{

}

void Inventory::Draw(HDC backDC, float DeltaTime)
{
	m_BitMap->Draw(backDC, 0, 0, 0);

	for (ItemSlot* slot : itemSlots)
	{
		if (slot->item != NULL)
		{
			slot->item->Draw(backDC, DeltaTime);
		}
	}

	//item->Draw(backDC, DeltaTime);
	//item->PosUpdate(SlotPos[0].X, SlotPos[0].Y);
}

void Inventory::Update(float DeltaTime, POINT mousePos)
{
	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) // Ű ��������
	{
		for (int i = 0; i < SLOT_COUNT; i++)
		{
			if (SlotPos[i].X < mousePos.x && SlotPos[i].X + SLOT_SIZEX > mousePos.x)
			{
				if (SlotPos[i].Y < mousePos.y && SlotPos[i].Y + SLOT_SIZEY > mousePos.y)
				{
					std::string integerVal = std::to_string(i);
					//�޼����� ���
					MessageBoxA(NULL, integerVal.c_str(), NULL, MB_OK);
				}
			}
		}
	}




	
}

bool Inventory::AddItem(Item* _item)
{
	for (ItemSlot* slot : itemSlots)
	{
		if (slot->item == NULL)
		{
			_item->itemPos = slot->pos;
			slot->item = _item;			
			return true;
		}
	}

	return false;
}

void Inventory::Reset()
{
}
