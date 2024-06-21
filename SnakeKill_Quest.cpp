#include "SnakeKill_Quest.h"

SnakeKill_Quest::SnakeKill_Quest() : Quest(QuestType_SnakeSkill)
{
	SnakeKillMax = 1; // 두마리 잡기
	currSnakeKill = 0;
	Complete = false;
}

SnakeKill_Quest::~SnakeKill_Quest()
{
}

void SnakeKill_Quest::OnNotify(QuestType type)
{
	if (type != this->Type) // 해당 타입의 퀘스트라면 
		return;

	currSnakeKill++; // 	
}

void SnakeKill_Quest::CompleateCheck()
{
	if (SnakeKillMax <= currSnakeKill)
	{
		CompleteAnim = true;
		Complete = true;
	}
}


void SnakeKill_Quest::Draw(HDC backDC, float DeltaTime)
{
	Quest::Draw(backDC, DeltaTime);
}

void SnakeKill_Quest::Reset()
{
}
