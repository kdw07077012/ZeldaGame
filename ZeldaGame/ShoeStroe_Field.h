#pragma once
#include "Field.h"
#include "ShoeNPC.h"
#include "NPC.h"

class ShoeStroe_Field : public Field
{
private:
	ShoeNPC* m_NPC;
	
public:
	ShoeStroe_Field();
	~ShoeStroe_Field();
	virtual void Init() override;
	virtual void Draw(HDC backDC, float DeltaTime) override;
	void Update(float DeltaTime);
	virtual void Reset() override;
	NPC* FieldNpcCollision(RECT rect);
	virtual bool Collision(RECT rect) override;  // 필드 콜리전 체크 
};

