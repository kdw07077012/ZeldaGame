#pragma once
enum QuestType
{
	QuestType_None,
	QuestType_ShoeHelp,
	QuestType_SnakeSkill,
};


//����Ʈ���� ���� Ŭ����
class Observer  
{
public:
	virtual void OnNotify(QuestType type = QuestType_None) = 0;
};

