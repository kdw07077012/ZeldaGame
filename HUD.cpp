#include "HUD.h"
#include "GameManager.h"
#include <math.h>
HUD::HUD()
{
	m_BitMap = BitMapManager::GetInstance()->GetBitMap(ImageType_HUD);
	m_HpBitmap_Size = { 30,30 };
	//30
	HPAnim = 0; // 0 Ǯ 5 �� ��Ʈ ���� 02
	player = GameManager::GetInstance()->GetPlayer();
	MaxHP = player->GetMaxHP();

	for (int i = 0; i < MaxHP; i++)
	{
		BitMap* hpbitmap = BitMapManager::GetInstance()->GetBitMap(ImageType_LikHp);
		m_HpBitmaps.push_back(hpbitmap);
	}


	ItemEquiqmentSlot[WEAPON_SLOT] = new ItemSlot;
	ItemEquiqmentSlot[EQUIPMENT_SLOT] = new ItemSlot;

	ItemEquiqmentSlot[WEAPON_SLOT]->IvenSlot = new Item(None, 19, 13, ItemImageType_HUD);
	ItemEquiqmentSlot[WEAPON_SLOT]->pos.X = 19;
	ItemEquiqmentSlot[WEAPON_SLOT]->pos.Y = 13;

	ItemEquiqmentSlot[EQUIPMENT_SLOT]->IvenSlot = new Item(None, 92, 13, ItemImageType_HUD);
	ItemEquiqmentSlot[EQUIPMENT_SLOT]->pos.X = 92;
	ItemEquiqmentSlot[EQUIPMENT_SLOT]->pos.Y = 13;
}

HUD::~HUD()
{
}


void HUD::Reset()
{
	ItemEquiqmentSlot[WEAPON_SLOT]->IvenSlot->item = None;
	ItemEquiqmentSlot[EQUIPMENT_SLOT]->IvenSlot->item = None;
}


void HUD::Draw(HDC backDC, float DeltaTime)
{
	ItemEquiqmentSlot[WEAPON_SLOT]->IvenSlot->Draw(backDC, DeltaTime);
	ItemEquiqmentSlot[EQUIPMENT_SLOT]->IvenSlot->Draw(backDC, DeltaTime);

	//player->GetHp();
	//(MaxHP % i) * 5
	m_BitMap->Draw(backDC, 0, 0, 1);
	float hp = player->GetHp();
	int i = 0, j = 0;
	for (i = 0; j < MaxHP; i++)
	{
		for (int k = 0; k < 5; k++, j++)
		{
			if (j >= MaxHP)
				return;

			if (hp >= j + 1)
			{
				m_HpBitmaps[j]->AnimationUpdate(backDC, 4, 450 + ((k + 1) * 30), (40 + (20 * (i))), m_HpBitmap_Size, 0.8f);
			}
			else
			{	// ���� ü���� �ش� ��Ʈ�Ǹ� ���������� �������� 1.0 �̻��϶� ������ ��Ʈ, 1.0 �����϶�
				if (fmodf(hp, j) < 1.0f) //��Ʈ �̹��� ������ 5�� 1.0 ������������ �ش� ���� hp�̹����� ����
				{
					m_HpBitmaps[j]->AnimationUpdate(backDC, fmodf(hp, j) * 5, 450 + ((k + 1) * 30), (40 + (20 * (i))), m_HpBitmap_Size, 0.8f);
				}
				else
				{
					m_HpBitmaps[j]->AnimationUpdate(backDC, 0, 450 + ((k + 1) * 30), (40 + (20 * (i))), m_HpBitmap_Size, 0.8f);
				}

			}
			
		}

		
	}
}

void HUD::Update(float DeltaTime)
{
}

void HUD::HPMaxAdd()
{
	BitMap* hpbitmap = BitMapManager::GetInstance()->GetBitMap(ImageType_LikHp);
	m_HpBitmaps.push_back(hpbitmap);
	MaxHP++;
}

void HUD::EquipmentedItem(EItem _item, bool eqippend)
{
	if (eqippend)
	{
		if (Item_Sword == _item)
			ItemEquiqmentSlot[WEAPON_SLOT]->IvenSlot->item = _item;
		else
			ItemEquiqmentSlot[EQUIPMENT_SLOT]->IvenSlot->item = _item;
	}
	else
	{
		if (Item_Sword == _item)
			ItemEquiqmentSlot[WEAPON_SLOT]->IvenSlot->item = None;
		else
			ItemEquiqmentSlot[EQUIPMENT_SLOT]->IvenSlot->item = None;
	}

	
}
