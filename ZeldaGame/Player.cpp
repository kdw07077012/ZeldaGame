#include "Player.h"

Player::Player()
{
	m_playerDirBitmap = BitMapManager::GetInstance()->GetPlayerDirBitmap();

	msize = BitMapManager::GetInstance()->GetWindowSize();
	m_pos.X = 0;
	m_pos.Y = 0;
	AnimationCount = 0;
	dir = DOWN;
	MaxAnimCount = 10;
	
	

}

Player::~Player()
{
	
}

void Player::PlayerInput(float DeltaTime)
{
	m_bmoveable = false;



	if (GetAsyncKeyState(0x57) && 0x8000) //W
	{
		m_bmoveable = true;
		dir = UP;
		m_pos.Y -= 500 * DeltaTime;
			
	}


	if (GetAsyncKeyState(0x53) && 0x8000) // S
	{
		m_bmoveable = true;
		dir = DOWN;
		m_pos.Y += 500 * DeltaTime;

			
	}

	if (GetAsyncKeyState(0x41) && 0x8000) // A
	{
		m_bmoveable = true;
		dir = LEFT;

		m_pos.X -= 500 * DeltaTime;


		
			
	}

	if (GetAsyncKeyState(0x44) && 0x8000) // D
	{

		m_bmoveable = true;
		dir = RIGHT;

		



		m_pos.X += 500 * DeltaTime;
			
	}
	
}


void Player::Draw(HDC backDC, float DeltaTime)
{
	Rectangle(backDC, (((msize.cx / 2) + (size.cx * 2)) - Camera::GetInstance()->GetX()) + m_pos.X,
		(((msize.cy / 2) + (size.cy * 2)) - Camera::GetInstance()->GetY()) + m_pos.Y,
		(((msize.cx / 2) + (size.cx * 2)) - Camera::GetInstance()->GetX()) + m_pos.X + size.cx * 2,
		(((msize.cy / 2) + (size.cy * 2)) - Camera::GetInstance()->GetY()) + m_pos.Y + size.cy * 2);


	player_rect = { (((msize.cx / 2) + (size.cx * 2)) - Camera::GetInstance()->GetX()) + m_pos.X,
		(((msize.cy / 2) + (size.cy * 2)) - Camera::GetInstance()->GetY()) + m_pos.Y,
		(((msize.cx / 2) + (size.cx * 2)) - Camera::GetInstance()->GetX()) + m_pos.X + size.cx * 2,
		(((msize.cy / 2) + (size.cy * 2)) - Camera::GetInstance()->GetY()) + m_pos.Y + size.cy * 2 };

	switch (dir)
	{
	case LEFT:
		if (m_bmoveable)
			m_playerDirBitmap.Left_Bitmap[PlayerState_WALK].AnimationUpdate(backDC, AnimationCount,
				(((msize.cx / 2) + (size.cx * 2)) - Camera::GetInstance()->GetX()) + m_pos.X,
				(((msize.cy / 2) + (size.cy * 2)) - Camera::GetInstance()->GetY()) + m_pos.Y,
				size, 2.0f);
		else
			m_playerDirBitmap.Left_Bitmap[PlayerState_IDLE].AnimationUpdate(backDC, AnimationCount,
				(((msize.cx / 2) + (size.cx * 2)) - Camera::GetInstance()->GetX()) + m_pos.X,
				(((msize.cy / 2) + (size.cy * 2)) - Camera::GetInstance()->GetY()) + m_pos.Y,
				size, 2.0f);
		break;
	case RIGHT:
		if (m_bmoveable)
			m_playerDirBitmap.Right_Bitmap[PlayerState_WALK].AnimationUpdate(backDC, AnimationCount,
				(((msize.cx / 2) + (size.cx * 2)) - Camera::GetInstance()->GetX()) + m_pos.X,
				(((msize.cy / 2) + (size.cy * 2)) - Camera::GetInstance()->GetY()) + m_pos.Y,
				size, 2.0f);
		else
			m_playerDirBitmap.Right_Bitmap[PlayerState_IDLE].AnimationUpdate(backDC, AnimationCount,
				(((msize.cx / 2) + (size.cx * 2)) - Camera::GetInstance()->GetX()) + m_pos.X,
				(((msize.cy / 2) + (size.cy * 2)) - Camera::GetInstance()->GetY()) + m_pos.Y,
				size, 2.0f);
		break;
	case UP:
		if (m_bmoveable)
			m_playerDirBitmap.Up_Bitmap[PlayerState_WALK].AnimationUpdate(backDC, AnimationCount,
				(((msize.cx / 2) + (size.cx * 2)) - Camera::GetInstance()->GetX()) + m_pos.X,
				(((msize.cy / 2) + (size.cy * 2)) - Camera::GetInstance()->GetY()) + m_pos.Y,
				size, 2.0f);
		else
			m_playerDirBitmap.Up_Bitmap[PlayerState_IDLE].AnimationUpdate(backDC, AnimationCount,
				(((msize.cx / 2) + (size.cx * 2)) - Camera::GetInstance()->GetX()) + m_pos.X,
				(((msize.cy / 2) + (size.cy * 2)) - Camera::GetInstance()->GetY()) + m_pos.Y,
				size, 2.0f);
		break;
	case DOWN:
		if (m_bmoveable)
			m_playerDirBitmap.Down_Bitmap[PlayerState_WALK].AnimationUpdate(backDC, AnimationCount,
				(((msize.cx / 2) + (size.cx * 2)) - Camera::GetInstance()->GetX()) + m_pos.X,
				(((msize.cy / 2) + (size.cy * 2)) - Camera::GetInstance()->GetY()) + m_pos.Y,
				size, 2.0f);
		else
			m_playerDirBitmap.Down_Bitmap[PlayerState_IDLE].AnimationUpdate(backDC, AnimationCount,
				(((msize.cx / 2) + (size.cx * 2)) - Camera::GetInstance()->GetX()) + m_pos.X,
				(((msize.cy / 2) + (size.cy * 2)) - Camera::GetInstance()->GetY()) + m_pos.Y,
				size, 2.0f);
		break;
	default:
		break;
	}

	//디버깅 드로우
	//std::string str = "Obstacle : " + std::to_string(Camera::GetInstance()->GetX());
	//TextOutA(backDC, 100, 0, str.c_str(), str.length());
	
	
	
}

void Player::Update(float DeltaTime)
{
	
	size.cx = 30;
	size.cy = 25;
	

	fMoveDeltaTime += DeltaTime;

	if (fMoveDeltaTime > 0.04f)
	{
		
		if (AnimationCount + 1 >= MaxAnimCount)
			AnimationCount = 1;
		else
			AnimationCount++;

		fMoveDeltaTime = 0.0f;
	}
}

void Player::Reset()
{
}

