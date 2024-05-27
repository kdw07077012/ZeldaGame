#pragma once
#include "Object.h"
class BackGround : public Object
{
private:
	int x, y;
	float m_fMoveDeltaTime;
public:
	BackGround();
	~BackGround();
	virtual void Draw(HDC backDC, float DeltaTime) override;
	void Update(float DeltaTime);
	virtual void Reset() override;
};

