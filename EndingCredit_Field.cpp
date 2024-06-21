#include "EndingCredit_Field.h"
#include "GameManager.h"
EndingCredit_Field::EndingCredit_Field()
{
	BackGroundBitmap = BitMapManager::GetInstance()->GetWindowBitMap();
	CreditBitmap = BitMapManager::GetInstance()->GetBitMap(ImageType_Credit);
	CreditSize = { 120,160 };
}

EndingCredit_Field::~EndingCredit_Field()
{
}

void EndingCredit_Field::Draw(HDC backDC, float DeltaTime)
{
	//BackGroundBitmap.Draw(backDC, 0, 0, 0);

    CreditBitmap[0].Draw(backDC, 0, 0, 0);
    CreditBitmap[1].CutDraw(backDC, 400, 100, AnimCount * CreditSize.cx, 0, CreditSize, 2.0f);
    CreditBitmap[2].Draw(backDC, 280, 450, 1);
    CreditBitmap[3].CutDraw(backDC, 100, 150, 0,0, CreditBitmap[3].GetSize(), 1.5f);

    AnimDeltaTime += DeltaTime;

    if (AnimDeltaTime > 0.4F)
    {
        if (AnimCount + 1 >= 8)
        {
      
            GameManager::GetInstance()->SetGameState(GAMESTATE_TITLE);

        }
        else
            AnimCount++;

        AnimDeltaTime = 0.0f;
    }

	
}

void EndingCredit_Field::Reset()
{
}
