#pragma once
#include "Quest.h"

class ShoeHelp_Quest : public Quest  // 신발가게 아저씨를 도와주는 퀘스트 
{
private:
	bool bShoeHelp;
public:
	ShoeHelp_Quest();
	~ShoeHelp_Quest();
	virtual void OnNotify(QuestType type) override;
	virtual void CompleateCheck() override;
	virtual void Draw(HDC backDC, float DeltaTime) override;
	virtual void Reset() override;
};

