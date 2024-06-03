#pragma once
#include "Field.h"

class Store_Field : public Field
{
private:
	BackGround* m_bShoeStroe;  // 신발 상점
	Obstacle* Field_Collision; // 필드 이동 콜리전 
	BackGround* m_bStoreRoom;  //  아이템 상점 
public:
	Store_Field();
	~Store_Field();
	virtual void Draw(HDC backDC, float DeltaTime) override;
	void Update(float DeltaTime);
	virtual void Reset() override;
	virtual bool Collision(RECT rect);  // 필드 콜리전 체크 

};

