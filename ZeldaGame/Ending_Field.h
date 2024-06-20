#pragma once
#include "Field.h"
class Ending_Field : public Field
{
private:
	BitMap* ZeldaBitmap;
	float AnimDeltaTime;
	float DelayTime;
	int AnimCount;
	bool bReset;
	RECT ZeldaCollision;
	bool bCollision;
public:
	Ending_Field();
	~Ending_Field();
	void Init();
	virtual void Draw(HDC backDC, float DeltaTime) override;
	void Update(float DeltaTime);
	void BackDraw(HDC backDC, float DeltaTime); //플레이어 위에그려야하는 이미지
	virtual void Reset() override;
	virtual bool Collision(RECT rect) override;  // 필드 콜리전 체크 
};

