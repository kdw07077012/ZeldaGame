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
	void BackDraw(HDC backDC, float DeltaTime); //�÷��̾� �����׷����ϴ� �̹���
	virtual void Reset() override;
	virtual bool Collision(RECT rect) override;  // �ʵ� �ݸ��� üũ 
};

