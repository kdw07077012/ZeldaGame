#pragma once
#include "Field.h"
#include "BossMonster.h"

class Boss_Field : public Field
{
private:
	BossMonster* m_BossMonster; 
	BitMap PortalBitmap;
	RECT PortalCollision;
	
public:
	Boss_Field();
	~Boss_Field();
	virtual void Init() override;
	virtual void Draw(HDC backDC, float DeltaTime) override;
	void Update(float DeltaTime);
	virtual void Reset() override;
	virtual bool Collision(RECT rect) override;  // 필드 콜리전 체크 
	void Boss_Collision(RECT rect);
};


