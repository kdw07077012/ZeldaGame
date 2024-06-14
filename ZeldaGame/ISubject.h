#pragma once
// 옵저버(퀘스트) 관리
#include "Quest.h"
class ISubject
{
public:
    virtual void AddObserver(Quest* o) = 0;
    virtual void RemoveObserver(Quest* o) = 0;
    virtual void Notify(QuestType type) = 0;
};