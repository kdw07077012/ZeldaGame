#include "Player.h"

Player::Player()
{
	m_playerDirBitmap = BitMapManager::GetInstance()->GetPlayerDirBitmap();

	SIZE msize = BitMapManager::GetInstance()->GetWindowSize();
	msize.cx /= 2;
	msize.cy /= 2;

	m_pos.X = msize.cx - 50;
	m_pos.Y = msize.cy;
	AnimationCount = 0;
	dir = DOWN;
}

Player::~Player()
{
	
}

void Player::PlayerInput(float DeltaTime)
{
	m_bmoveable = false;



	if (GetAsyncKeyState(0x57) && 0x8000) //W
	{
		m_pos.Y -= 2;
		m_bmoveable = true;
		dir = UP;
	}


	if (GetAsyncKeyState(0x53) && 0x8000) // S
	{
		m_pos.Y += 2;
		m_bmoveable = true;
		dir = DOWN;
	}

	if (GetAsyncKeyState(0x41) && 0x8000) // A
	{
		m_pos.X -= 2;
		m_bmoveable = true;
		dir = LEFT;
	}

	if (GetAsyncKeyState(0x44) && 0x8000) // D
	{

		m_pos.X += 2;
		m_bmoveable = true;
		dir = RIGHT;
	}
	
}


void Player::Draw(HDC backDC, float DeltaTime)
{
	//m_playerDirBitmap = BitMapManager::GetInstance()->GetPlayerDirBitmap();
	

	int screenPosX = (m_pos.X + Camera::GetInstance()->GetX() * 0.01f);
	int screenPosY = (m_pos.Y + Camera::GetInstance()->GetY() * 0.01f);

	
	


	switch (dir)
	{
	case LEFT:
		if (m_bmoveable)
			m_playerDirBitmap.Left_Bitmap[PlayerState_WALK].AnimationUpdate(backDC, AnimationCount, m_pos.X, m_pos.Y, size, 1.5f);
		else
			m_playerDirBitmap.Left_Bitmap[PlayerState_IDLE].AnimationUpdate(backDC, AnimationCount, m_pos.X, m_pos.Y, size, 1.5f);
		break;
	case RIGHT:
		if (m_bmoveable)
			m_playerDirBitmap.Right_Bitmap[PlayerState_WALK].AnimationUpdate(backDC, AnimationCount, m_pos.X, m_pos.Y, size, 1.5f);
		else
			m_playerDirBitmap.Right_Bitmap[PlayerState_IDLE].AnimationUpdate(backDC, AnimationCount, m_pos.X, m_pos.Y, size, 1.5f);
		break;
	case UP:
		if (m_bmoveable)
			m_playerDirBitmap.Up_Bitmap[PlayerState_WALK].AnimationUpdate(backDC, AnimationCount, m_pos.X, m_pos.Y, size, 1.5f);
		else
			m_playerDirBitmap.Up_Bitmap[PlayerState_IDLE].AnimationUpdate(backDC, AnimationCount, m_pos.X, m_pos.Y, size, 1.5f);
		break;
	case DOWN:
		if (m_bmoveable)
			m_playerDirBitmap.Down_Bitmap[PlayerState_WALK].AnimationUpdate(backDC, AnimationCount, m_pos.X, m_pos.Y, size, 1.5f);
		else
			m_playerDirBitmap.Down_Bitmap[PlayerState_IDLE].AnimationUpdate(backDC, AnimationCount, m_pos.X, m_pos.Y, size, 1.5f);
		break;
	default:
		break;
	}


	
	
	
}

void Player::Update(float DeltaTime)
{
	

	if (m_bmoveable)
	{
		size.cx = 29;
		MaxAnimCount = 10;
	}
	else
	{
		size.cx = 30;
		MaxAnimCount = 10;
	}

	size.cy = 25;


	fMoveDeltaTime += DeltaTime;

	if (fMoveDeltaTime > 0.1f)
	{
		AnimationCount++;
		if (AnimationCount >= MaxAnimCount)
			AnimationCount = 1;
		fMoveDeltaTime = 0.0f;
	}
}

void Player::Reset()
{
}
