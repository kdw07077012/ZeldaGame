#pragma once
#include "Field.h"
class Dungeon_Field : public Field
{
public:
	Dungeon_Field();
	~Dungeon_Field();
	void Init();
	virtual void Draw(HDC backDC, float DeltaTime) override;
	void Update(float DeltaTime);
	void BackDraw(HDC backDC, float DeltaTime); //�÷��̾� �����׷����ϴ� �̹���
	virtual void Reset() override;
	virtual bool Collision(RECT rect) override;  // �ʵ� �ݸ��� üũ 
};

