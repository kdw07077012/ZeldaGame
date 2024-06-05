#pragma once
#include "Field.h"

class Store_Field : public Field
{
private:

	BackGround* m_bShoeStroe;  // �Ź� ����
	BackGround* m_bStoreRoom;  //  ������ ���� 
public:
	Store_Field();
	~Store_Field();
	void Init();
	virtual void Draw(HDC backDC, float DeltaTime) override;
	void Update(float DeltaTime);
	void BackDraw(HDC backDC, float DeltaTime); //�÷��̾� �����׷����ϴ� �̹���
	virtual void Reset() override;
	virtual bool Collision(RECT rect) override;  // �ʵ� �ݸ��� üũ 

};

