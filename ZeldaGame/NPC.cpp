#include "NPC.h"
#include "Camera.h"
NPC::NPC()
{
	m_BitMap = BitMapManager::GetInstance()->GetBitMap(ImageType_NPC);
	m_NpcTextBar = BitMapManager::GetInstance()->GetBitMap(ImageType_NPCTextBar);
	fMoveDeltaTime = 0.0f;
	AnimationCount = 0;
	MaxAnimCount = 6;
	fAnimSpeed = 0.05f;
	bCollision = false;
	Collision = { 0,0,0,0 };
}

NPC::~NPC()
{
}

void NPC::Reset()
{
}
