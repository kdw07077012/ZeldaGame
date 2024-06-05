#pragma once
#include "Object.h"

enum EItem
{
	Item_Bow,	    // Ȱ
	Item_Fire,		// ���
	Item_Shield,	// ����
	Item_HeartAdd, // ü���߰�
	
};


class Item : public Object
{
private:
public:
	Item(EItem _item, int x, int y, bool InGame); //�ΰ��� �������Ͻ� true
	~Item();
	EItem item; //���� ������
	Position itemPos;
	virtual void Draw(HDC backDC, float DeltaTime) override;
	void PosUpdate(int x, int y);

	virtual void Reset() override;
};

