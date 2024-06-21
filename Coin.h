#pragma once
#include "Object.h"


class Coin : public Object
{
private:
	RECT collision;
	int RandomCoinBitCount;
	int CoinIndex;
public:
	Coin(int x, int y);
	~Coin();
	bool CoinPickup;
	virtual void Draw(HDC backDC, float DeltaTime) override;
	void Update(float DeltaTime);
	virtual void Reset() override;
	RECT& GetCollision() { return collision; }
	int GetCoinIndex() const { return CoinIndex; }
};

