#pragma once
#include "Object.h"

enum EItem
{
	None,
	Item_Bow,	    // Ȱ
	Item_Fire,		// ���
	Item_Shield,	// ����
	Item_Boomerang, // �θ޶�
	
};


class Item : public Object
{

public:
	Item(EItem _item);
	~Item();
	EItem item; //���� ������
	Position itemPos;
	virtual void Draw(HDC backDC, float DeltaTime) override;
	void PosUpdate(int x, int y);

	virtual void Reset() override;
};

