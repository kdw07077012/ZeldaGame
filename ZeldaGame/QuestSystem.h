#pragma once
#include "Object.h"
#include "ISubject.h"
#include "vector"
class QuestSystem : public Object, ISubject
{
private:
    std::vector<Quest*> Quests;
public:
    bool Enabled; //퀘스트 창이 켜져있는지
public:
    QuestSystem();
    ~QuestSystem();
    virtual void Draw(HDC backDC, float DeltaTime) override;
    void QuestComplete_Draw(HDC backDC, float DeltaTime);
    void Update(float DeltaTime);
    virtual void Reset() override;
public:
    void AddObserver(Quest* o);
    void RemoveObserver(Quest* o);
    void Notify(QuestType type);
    Quest* FindQuest(QuestType type);

};

