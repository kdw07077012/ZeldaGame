#pragma once
#include "Field.h"

class Store_Field : public Field
{
private:

	BackGround* m_bShoeStroe;  // 신발 상점
	BackGround* m_bStoreRoom;  //  아이템 상점 
public:
	Store_Field();
	~Store_Field();
	void Init();
	virtual void Draw(HDC backDC, float DeltaTime) override;
	void Update(float DeltaTime);
	void BackDraw(HDC backDC, float DeltaTime); //플레이어 위에그려야하는 이미지
	virtual void Reset() override;
	virtual bool Collision(RECT rect) override;  // 필드 콜리전 체크 

};

