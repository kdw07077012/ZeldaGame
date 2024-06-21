#include "ShoeHelp_Quest.h"

ShoeHelp_Quest::ShoeHelp_Quest() : Quest(QuestType_ShoeHelp)
{
	bShoeHelp = false;
}

ShoeHelp_Quest::~ShoeHelp_Quest()
{
}

void ShoeHelp_Quest::OnNotify(QuestType type)
{
	if (type != this->Type) // 해당 타입의 퀘스트라면 
		return;

	bShoeHelp = true;
}

void ShoeHelp_Quest::CompleateCheck()
{
	if (bShoeHelp)
	{
		CompleteAnim = true;
		Complete = true;
	}
}

void ShoeHelp_Quest::Draw(HDC backDC, float DeltaTime)
{
	Quest::Draw(backDC, DeltaTime); // 부모 그리기 호출 
}

void ShoeHelp_Quest::Reset()
{
}
