#pragma once
#include "Quest.h"

class ShoeHelp_Quest : public Quest  // �Ź߰��� �������� �����ִ� ����Ʈ 
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

