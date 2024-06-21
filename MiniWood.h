#pragma once
#include "Object.h"
class MiniWood : public Object
{
private:
	RECT collision;
public:
	MiniWood(int x, int y);
	~MiniWood();
	virtual void Draw(HDC backDC, float DeltaTime) override;
	void Update(float DeltaTime);
	virtual void Reset() override;
	RECT& GetCollision() { return collision; }
};

