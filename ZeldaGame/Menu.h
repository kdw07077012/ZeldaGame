#pragma once
#include "Object.h"

enum GAMESTATE
{
	GAMESTATE_MENU,
	GAMESTATE_START,
};


class Menu : public Object
{
	Menu();
	~Menu();

	virtual void Draw(HDC backDC, float DeltaTime) override;
	void Update(float DeltaTime);

	virtual void Reset() override;
};

