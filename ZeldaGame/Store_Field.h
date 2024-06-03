#pragma once
#include "Field.h"

class Store_Field : public Field
{
private:
	BackGround* m_bShoeStroe;  // �Ź� ����
	Obstacle* Field_Collision; // �ʵ� �̵� �ݸ��� 
	BackGround* m_bStoreRoom;  //  ������ ���� 
public:
	Store_Field();
	~Store_Field();
	virtual void Draw(HDC backDC, float DeltaTime) override;
	void Update(float DeltaTime);
	virtual void Reset() override;
	virtual bool Collision(RECT rect);  // �ʵ� �ݸ��� üũ 

};

