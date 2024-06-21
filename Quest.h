#pragma once
#include "Object.h"
#include "Observer.h"



class Quest : public Object, Observer
{
protected:
	QuestType Type;
	SIZE size;

	BitMap m_ComplateBitmap;
	bool Complete; // 퀘스트 달성
	bool CompleteAnim; // 컴플리트 표시 텍스트 애니메이션 활성화
	float drawDeltaTime;
public:
	Quest(QuestType type);
	~Quest();
	virtual void OnNotify(QuestType type) override;
	virtual void Draw(HDC backDC, float DeltaTime) override;
	virtual void Complate_Draw(HDC backDC, float DeltaTime);
	virtual void CompleateCheck() = 0;
	virtual void Reset() override;
	bool GetComplete() const { return Complete; }
	QuestType GetQuestType() const { return Type; }
};

