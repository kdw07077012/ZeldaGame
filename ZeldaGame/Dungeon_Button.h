#pragma once
#include "Object.h"
#include "Treasure_Chest.h"
#include "vector"
struct Button
{
	Position pos;
	BitMap button;
	SIZE size;
	bool pressed = false; // ���ȴ���
	RECT collision;
};


class Dungeon_Button : public Object
{
private:
	SIZE m_size;
	std::vector<Button*> m_buttons;
	int m_ButtonCount;
	bool Torchlight; //ȶ������
public:
	Dungeon_Button(int x, int y, int _ButtonCount, int y0ffset, bool torchlight = false, int X0ffset = 0); //requital 0 : ��, 1: ��������
	~Dungeon_Button();
	virtual void Draw(HDC backDC, float DeltaTime) override;
	void ButtonCollision(RECT rect);
	bool ButtonCheck();
	bool GetTorchlight() const { return Torchlight; }
	virtual void Update(float DeltaTime);
	virtual void Reset() override;
};

