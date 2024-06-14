#pragma once
#include "Quest.h"


class SnakeKill_Quest : public Quest
{
private: // 뱀 
	int currSnakeKill; // 스네이크 몇마리잡았는지
	int SnakeKillMax; // 최대 몇마리까지?
public:
	SnakeKill_Quest();
	~SnakeKill_Quest();
	virtual void OnNotify(QuestType type) override;
	virtual void CompleateCheck() override;
	virtual void Draw(HDC backDC, float DeltaTime) override;
	virtual void Reset() override;
};

