#pragma once
#include "Field.h"
#include "Dungeon_Button.h"
#include "Treasure_Chest.h"
#include "OctorocMonster.h"

#define MAX_BUTTON_COUNT 5
#define MAX_CHEST_COUNT 2
#define MAX_MONSTER_COUNT 3
class Dungeon_Field : public Field
{
private:
	Dungeon_Button* dungeon_Button[MAX_BUTTON_COUNT];

	BitMap RoadBitmap;
	BitMap DoorBitmap[2];
	RECT Object_collision[3];
	Treasure_Chest* Chest[MAX_CHEST_COUNT]; //���� ����

	OctorocMonster* octorocMonster[MAX_MONSTER_COUNT];
	
public:
	Dungeon_Field();
	~Dungeon_Field();
	void Init();
	virtual void Draw(HDC backDC, float DeltaTime) override;
	void Update(float DeltaTime);
	void BackDraw(HDC backDC, float DeltaTime); //�÷��̾� �����׷����ϴ� �̹���
	virtual void Reset() override;
	virtual bool Collision(RECT rect) override;  // �ʵ� �ݸ��� üũ 
	void Monsters_Collision(RECT rect);
};

