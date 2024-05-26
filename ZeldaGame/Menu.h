#pragma once
#include "Object.h"

enum GAMESTATE
{
	GAMESTATE_TITLE,
	GAMESTATE_MENU,
	GAMESTATE_START,
};


class Menu : public Object
{
public:
	Menu();
	~Menu();

	float TitleDeltaTime = 0;
	int TitleCountindex = 0;

	virtual void Draw(HDC backDC, float DeltaTime) override;
	void Update(float DeltaTime);

	virtual void Reset() override;
};

