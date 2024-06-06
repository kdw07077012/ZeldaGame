#pragma once
#include "Object.h"
#include "Coin.h"

enum dstrObjType //파괴가능오브젝트 타입
{
	dstrObjType_Thicket,
	dstrObjType_Jar,
};

class dstrObj : public Object //파괴 가능 오브젝트
{
private:
	RECT collision;
	Coin* m_coin;
	SIZE m_size;
	dstrObjType m_type;

	float JarAimTimer;
public:
	dstrObj(dstrObjType Type, int x, int y);
	~dstrObj();

	bool Attacked;
	float fAnimDeltaTime;
	int JarAnimCount;
	virtual void Draw(HDC backDC, float DeltaTime) override;
	void Update(float DeltaTime);
	void AttackedObject();

	int CoinPickup()
	{
		m_coin->CoinPickup = true;
		return m_coin->GetCoinIndex();
	}
	virtual void Reset() override;
	bool GetCoinPickup() { return m_coin->CoinPickup; }
	RECT& GetCollision() {
		if (Attacked)
			return m_coin->GetCollision();
		else
			return collision;
		}
};

