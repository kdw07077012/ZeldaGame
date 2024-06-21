#pragma once
#include "Quest.h"


class SnakeKill_Quest : public Quest
{
private: // �� 
	int currSnakeKill; // ������ũ �����Ҵ���
	int SnakeKillMax; // �ִ� �������?
public:
	SnakeKill_Quest();
	~SnakeKill_Quest();
	virtual void OnNotify(QuestType type) override;
	virtual void CompleateCheck() override;
	virtual void Draw(HDC backDC, float DeltaTime) override;
	virtual void Reset() override;
};

