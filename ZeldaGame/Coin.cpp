#include "Coin.h"
#include "Camera.h"

#include<ctime>

Coin::Coin(int x, int y) : Object(x,y)
{
	srand(time(NULL));
	m_BitMap = BitMapManager::GetInstance()->GetBitMap(ImageType_Coin);
	RandomCoinBitCount = rand() % 2;
	collision = { 0,0,0,0 };
	CoinPickup = false;
	CoinIndex = (RandomCoinBitCount + 1) * 50;
}

Coin::~Coin()
{
}

void Coin::Draw(HDC backDC, float DeltaTime)
{
	if (CoinPickup)
		return;

	SIZE msize = BitMapManager::GetInstance()->GetWindowSize();
	SIZE size = { 21,15 };
	int screenX = (((msize.cx / 2) - (size.cx * 2)) - Camera::GetInstance()->GetX()) + m_ix;
	int screenY = (((msize.cy / 2) - (size.cy * 2)) - Camera::GetInstance()->GetY()) + m_iy;

	collision = { screenX, screenY, screenX + size.cx * 2 , screenY + size.cy * 2 };

	m_BitMap->AnimationUpdate(backDC, RandomCoinBitCount, screenX, screenY, size, 2.0f);

}

void Coin::Update(float DeltaTime)
{
}

void Coin::Reset()
{
}
