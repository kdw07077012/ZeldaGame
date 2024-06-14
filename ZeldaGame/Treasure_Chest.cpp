#include "Treasure_Chest.h"
#include "Camera.h"
#include<ctime>
#include "GameManager.h"
Treasure_Chest::Treasure_Chest(int x, int y) : Object(x,y)
{
	srand(time(NULL));
	ChestDraw = false;
	m_BitMap = BitMapManager::GetInstance()->GetBitMap(ImageType_Treasure_Chest);
	size = { 20,16 };
	collision = { 0,0,0,0 };
	Event_Collision = { 0,0,0,0 };
	BoxOpen = false;
	// 랜덤적으로 포션과 체력증가, 코인 중 드랍
	Drop_item = new Item(rand() % 2 ? Item_Shield : Item_Lanton, x - DROP_ITEM_OFFSET, y + DROP_ITEM_OFFSET, ItemImageType_InGame);
	Drop_Coin = new Coin(x, y);

	//랜덤적으로 아이템 , 코인 중선택
	if (rand() % 2)
		bItem = true;
	else
		bItem = false;
		
	ItemPickup = false;
}

Treasure_Chest::~Treasure_Chest()
{

}

void Treasure_Chest::Draw(HDC backDC, float DeltaTime)
{
	SIZE msize = BitMapManager::GetInstance()->GetWindowSize();
	int screenX = (((msize.cx / 2) - (size.cx * 2)) - Camera::GetInstance()->GetX()) + m_ix;
	int screenY = (((msize.cy / 2) - (size.cy * 2)) - Camera::GetInstance()->GetY()) + m_iy;

	collision = { screenX, screenY, screenX + size.cx * 2 , screenY + size.cy * 2 };
	Event_Collision = { screenX, screenY - (size.cx), screenX + size.cx * 2 , screenY + size.cy * 2};

	m_BitMap->AnimationUpdate(backDC, BoxOpen, screenX, screenY, size, 2.0f);
	//Rectangle(backDC, collision.left, collision.top, collision.right, collision.bottom);

	if (BoxOpen && !ItemPickup)
	{
		if (bItem)
			Drop_item->Draw(backDC, DeltaTime);
		else
			Drop_Coin->Draw(backDC, DeltaTime);
	}
	
}

void Treasure_Chest::Update(float DeltaTime)
{
}

void Treasure_Chest::Collision()
{
	if (BoxOpen && !ItemPickup)
	{
		if (bItem)
		{
			GameManager::GetInstance()->useItem(InGame_Item(Drop_item->item));
		}
		else
		{
		}
		{
			GameManager::GetInstance()->GetPlayer()->AddCoin(Drop_Coin->GetCoinIndex());
		}

		ItemPickup = true;

	}

}


// 바로 체력증가
void Treasure_Chest::Reset()
{
}
