#pragma once
enum QuestType
{
	QuestType_None,
	QuestType_ShoeHelp,
	QuestType_SnakeSkill,
};


//퀘스트들을 만들 클래스
class Observer  
{
public:
	virtual void OnNotify(QuestType type = QuestType_None) = 0;
};

