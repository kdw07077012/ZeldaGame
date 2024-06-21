#pragma once
#include "Object.h"
#include "BitMapManager.h"
#include "ItemSlot.h"
#include <vector>
#include "Player.h"

#define WEAPON_SLOT	   0
#define EQUIPMENT_SLOT 1


class HUD : public Object
{
private:
	ItemSlot* ItemEquiqmentSlot[2]; //æ∆¿Ã≈€ ¿Â¬¯ΩΩ∑‘
	std::vector<BitMap*> m_HpBitmaps;
	SIZE m_HpBitmap_Size;
	int MaxHP;
	int HPAnim;
	Player* player;
public:
	HUD();
	~HUD();
	virtual void Draw(HDC backDC, float DeltaTime) override;
	void Update(float DeltaTime);
	void HPMaxAdd();
	void EquipmentedItem(EItem _item, bool eqippend);

	virtual void Reset() override;
};

