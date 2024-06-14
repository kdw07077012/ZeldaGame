#pragma once
// ������(����Ʈ) ����
#include "Quest.h"
class ISubject
{
public:
    virtual void AddObserver(Quest* o) = 0;
    virtual void RemoveObserver(Quest* o) = 0;
    virtual void Notify(QuestType type) = 0;
};