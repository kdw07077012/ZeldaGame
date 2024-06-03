#pragma once
#include "Object.h"
#include "BitMapManager.h"

class HUD : public Object
{
public:
	HUD();
	~HUD();
	virtual void Draw(HDC backDC, float DeltaTime) override;
	void Update(float DeltaTime);

	virtual void Reset() override;
};

