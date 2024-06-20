#pragma once
#include "Field.h"
class EndingCredit_Field : public Field
{
private:
	BitMap BackGroundBitmap;
	BitMap* CreditBitmap;
	SIZE CreditSize;
	float AnimDeltaTime;
	float DelayTime;
	int AnimCount;
public:
	EndingCredit_Field();
	~EndingCredit_Field();
	virtual void Draw(HDC backDC, float DeltaTime) override;
	virtual void Reset() override;
};

