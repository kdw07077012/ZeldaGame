#pragma once
#include "Object.h"
#include "Camera.h"
class BackGround : public Object
{
private:
	Position tPos;
	Position pos;
	float m_fMoveDeltaTime;
	int screenPosX;
	int screenPosY;
	FieldType field; // 현재 필드
public:
	BackGround(FieldType fieldtype);
	~BackGround();
	virtual void Draw(HDC backDC, float DeltaTime) override;
	void Update(float DeltaTime);
	virtual void Reset() override;
	FieldType GetFieldType() const { return field; }

};

