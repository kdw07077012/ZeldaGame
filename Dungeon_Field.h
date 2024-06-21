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
	Treasure_Chest* Chest[MAX_CHEST_COUNT]; //보상 상자

	OctorocMonster* octorocMonster[MAX_MONSTER_COUNT];
	
public:
	Dungeon_Field();
	~Dungeon_Field();
	void Init();
	virtual void Draw(HDC backDC, float DeltaTime) override;
	void Update(float DeltaTime);
	void BackDraw(HDC backDC, float DeltaTime); //플레이어 위에그려야하는 이미지
	virtual void Reset() override;
	virtual bool Collision(RECT rect) override;  // 필드 콜리전 체크 
	void Monsters_Collision(RECT rect);
};

