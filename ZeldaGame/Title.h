#pragma once
#include "Object.h"
#include <conio.h>

#define TITLE_LOOP 88

class Title : public Object
{
private:
	bool m_bloop = false;
	bool m_bGameState = false;
	float TitleDeltaTime = 0.0f;
	int TitleCountindex = 0;

public:
	Title();
	~Title();

	void PlaySelect();
	virtual void Draw(HDC backDC, float DeltaTime) override;
	void Update(float DeltaTime);

	virtual void Reset() override;
	bool GetGameState() const { return m_bGameState; }
};

