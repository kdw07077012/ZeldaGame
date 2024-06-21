#include "QuestSystem.h"

QuestSystem::QuestSystem()
{
	m_BitMap = BitMapManager::GetInstance()->GetBitMap(ImageType_QuestMenu);
	Enabled = false;

}

QuestSystem::~QuestSystem()
{
}

void QuestSystem::Draw(HDC backDC, float DeltaTime)
{
	m_BitMap->Draw(backDC, 0, 0, 0);

	for (auto Quest : Quests)
	{
		Quest->Draw(backDC, DeltaTime);
	}

}

void QuestSystem::QuestComplete_Draw(HDC backDC, float DeltaTime)
{
	for (auto Quest : Quests)
	{
		if (Quest->GetComplete())
		{
			Quest->Complate_Draw(backDC, DeltaTime);
		}
	}
}

void QuestSystem::Update(float DeltaTime)
{
}

void QuestSystem::Reset()
{
}


void QuestSystem::AddObserver(Quest* o)
{
	if (Quests.size() <= 3)
	{
		Quests.push_back(o);
	}
}

void QuestSystem::RemoveObserver(Quest* o)
{
}

void QuestSystem::Notify(QuestType type) // 옵저버들에게 메시지 전달
{
	for (auto Quest : Quests)
	{
		Quest->OnNotify(type);
	}
}

Quest* QuestSystem::FindQuest(QuestType type)
{
	for (auto quest : Quests)
	{
		if (quest->GetQuestType() == type)
			return quest;
	}

	return NULL;
}

