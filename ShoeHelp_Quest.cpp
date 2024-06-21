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
	if (type != this->Type) // �ش� Ÿ���� ����Ʈ��� 
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
	Quest::Draw(backDC, DeltaTime); // �θ� �׸��� ȣ�� 
}

void ShoeHelp_Quest::Reset()
{
}
