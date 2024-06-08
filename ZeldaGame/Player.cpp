#include "Player.h"
#include "GameManager.h"
Player::Player()
{
	m_playerDirBitmap[LEFT] = BitMapManager::GetInstance()->GetPlayerDirBitmap().Left_Bitmap;
	m_playerDirBitmap[RIGHT] = BitMapManager::GetInstance()->GetPlayerDirBitmap().Right_Bitmap;
	m_playerDirBitmap[UP] = BitMapManager::GetInstance()->GetPlayerDirBitmap().Up_Bitmap;
	m_playerDirBitmap[DOWN] = BitMapManager::GetInstance()->GetPlayerDirBitmap().Down_Bitmap;

	m_playerSkillDirBitmap[UP] = BitMapManager::GetInstance()->GetPlayerDirBitmap(true).Up_Bitmap;
	m_playerSkillDirBitmap[DOWN] = BitMapManager::GetInstance()->GetPlayerDirBitmap(true).Down_Bitmap;
	m_playerSkillDirBitmap[LEFT] = BitMapManager::GetInstance()->GetPlayerDirBitmap(true).Left_Bitmap;
	m_playerSkillDirBitmap[RIGHT] = BitMapManager::GetInstance()->GetPlayerDirBitmap(true).Right_Bitmap;


	msize = BitMapManager::GetInstance()->GetWindowSize();
	m_pos.X = 650;
	m_pos.Y = 372;
	AnimationCount = 0;
	dir = DOWN;
	MaxAnimCount = 10;
	m_playerState = PlayerState_IDLE;
	AnimLoop = true;
	fAnimSpeed = 0.04f;

	size.cx = 30;
	size.cy = 25;
	Skill = false;
	CoinCount = 1000;

	Equipment[0] = None;
	Equipment[1] = None;

	PlayerMaxHP = 5;
	PlayerHP = 4.4f;
}

//976 633
Player::~Player()
{
	
}

void Player::AddCoin(int Count)
{
	CoinCount += Count;
}
void Player::RemvoeCoin(int Count)

{
	CoinCount -= Count;
}

void Player::AttackCheck()
{
	RECT rect = player_rect;
	SIZE size = { 30, 25 };

	switch (dir)
	{
	case LEFT:
		rect.left = player_rect.left - (size.cx / 2);
		rect.right = player_rect.right - (size.cx / 2);
		break;
	case RIGHT:
		rect.left = player_rect.left + (size.cx / 2);
		rect.right = player_rect.right + (size.cx / 2);
		break;
	case UP:
		rect.top = player_rect.top - (size.cy / 2);
		rect.bottom = player_rect.bottom - (size.cy);
		break;
	case DOWN:
		rect.top = player_rect.top + (size.cy);
		rect.bottom = player_rect.bottom + (size.cy / 2);
		break;
	default:
		break;
	}



	if (GameManager::GetInstance()->FieldObject_AttackCollision(rect))
	{
		
	}
}

bool Player::PlayerInput(float DeltaTime)
{
	if (m_playerState >= PlayerState_FALLWATER || bHit)
		return false;

	m_bmoveable = false;
	RECT rect = player_rect;


	if (GetAsyncKeyState(0x4A) && 0x8000 && Equipment[0] == Item_Sword) // J : 공격 무기를장착했을시
	{
		m_playerState = PlayerState_Attack;
		Skill = true;
		AnimationCount = 1;
		MaxAnimCount = 8;
		
		size.cx = 200;
		size.cy = 200;

		AttackCheck();
	}


	if (GetAsyncKeyState(0x57) && 0x8000) //W
	{
		rect.top = player_rect.top - (size.cy / 2);
		rect.bottom = player_rect.bottom - (size.cy);
		int Temp = m_pos.Y;
		m_bmoveable = true;
		dir = UP;
		Temp -= 500 * DeltaTime;


		if (GameManager::GetInstance()->FieldCollision(rect) == false)
		{
			m_pos.Y = Temp;

			if (m_pos.Y > Camera::GetInstance()->GetY())
			{
				return false;
			}

			return true;
		}

		return false;
	}
	else if (GetAsyncKeyState(0x41) && 0x8000) // A
	{
		rect.left = player_rect.left - (size.cx / 2);
		rect.right = player_rect.right - (size.cx / 2);
		int Temp = m_pos.X;
		m_bmoveable = true;
		dir = LEFT;
		Temp -= 500 * DeltaTime;


		if (GameManager::GetInstance()->FieldCollision(rect) == false)
		{
			m_pos.X = Temp;

		
			if (m_pos.X > Camera::GetInstance()->GetX())
			{
				return false;
			}

			return true;
		}

		

		return false;


	} 
	else if (GetAsyncKeyState(0x53) && 0x8000) // S
	{
		rect.top = player_rect.top + (size.cy );
		rect.bottom = player_rect.bottom + (size.cy / 2);
		int Temp = m_pos.Y;
		m_bmoveable = true;
		dir = DOWN;
		Temp += 500 * DeltaTime;


		if (GameManager::GetInstance()->FieldCollision(rect) == false)
		{
			m_pos.Y = Temp;

			if (m_pos.Y < Camera::GetInstance()->GetY())
			{
				return false;
			}

			return true;
		}

		return false;
	}
	else if (GetAsyncKeyState(0x44) && 0x8000) // D
	{
		rect.left = player_rect.left + (size.cx / 2);
		rect.right = player_rect.right + (size.cx / 2);
		int Temp = m_pos.X;
		m_bmoveable = true;
		dir = RIGHT;
		Temp += 500 * DeltaTime;



		if (GameManager::GetInstance()->FieldCollision(rect) == false)
		{
			m_pos.X = Temp;

			if (m_pos.X < Camera::GetInstance()->GetX())
			{
				return false;
			}



			return true;
		}

		

		return false;

	}

	return false;
	
}


void Player::Draw(HDC backDC, float DeltaTime)
{
	int screenX = 0;
	int screenY = 0;

	

	

	//화면 중심 좌표에서 카메라랜더링 좌표값과 플레이어윈도우 좌표값 대입
	if (Skill)
	{
		screenX = (((msize.cx / 2) - (size.cx / 2)) - Camera::GetInstance()->GetX()) + m_pos.X;
		screenY = (((msize.cy / 2) - (size.cy / 2)) - Camera::GetInstance()->GetY()) + m_pos.Y;
	}
	else
	{
		screenX = (((msize.cx / 2) - (size.cx * 2)) - Camera::GetInstance()->GetX()) + m_pos.X;
		screenY = (((msize.cy / 2) - (size.cy * 2)) - Camera::GetInstance()->GetY()) + m_pos.Y;
	}

	int AttackX = (((msize.cx / 2) - (30 * 2)) - Camera::GetInstance()->GetX()) + m_pos.X;
	int AttackY = (((msize.cy / 2) - (25 * 2)) - Camera::GetInstance()->GetY()) + m_pos.Y;

	player_rect = { AttackX + 10, AttackY, AttackX + 30 * 2 - 10, AttackY + 25 * 2};

	std::string str = "m_posX : " + std::to_string(PlayerHP);
	TextOutA(backDC, 200, 50, str.c_str(), str.length());

#ifdef DEBUG
	//디버깅 드로우
	std::string str = "m_posX : " + std::to_string(m_pos.X);
	TextOutA(backDC, 200, 50, str.c_str(), str.length());
	std::string str2 = "m_posY : " + std::to_string(m_pos.Y);
	TextOutA(backDC, 200, 70, str2.c_str(), str2.length());
	std::string str1 = "Camera : " + std::to_string(Camera::GetInstance()->GetX());
	TextOutA(backDC, 200, 100, str1.c_str(), str1.length());

	RECT rect = player_rect;
	rect.left = player_rect.left;
	rect.right = player_rect.right;
	Rectangle(backDC, rect.left,
		rect.top,
		rect.right,
		rect.bottom);

#endif

	


	if (m_playerState == PlayerState_FALLWATER)
	{
		m_playerDirBitmap[dir][PlayerState_FALLWATER].AnimationUpdate(backDC, AnimationCount,
			screenX,
			screenY, size, 2.0f);
		AnimLoop = false;
		fAnimSpeed = 0.1f;


		if (AnimationCount >= MaxAnimCount - 1)
		{
			
			
			switch (dir)
			{
			case LEFT:
				break;
			case RIGHT:
				break;
			case UP:
				m_pos.Y += size.cy;
				break;
			case DOWN:
				m_pos.Y -= size.cy;
				break;
			default:
				break;
			}
			AnimLoop = true;
			fAnimSpeed = 0.04;
			m_playerState = PlayerState_IDLE;
			AnimationCount = 1;
			bHit = true;
			m_bmoveable = false;

		}
	}
	else if (m_playerState == PlayerState_Attack)
	{
		m_playerSkillDirBitmap[dir]->AnimationUpdate(backDC, AnimationCount,
			screenX,
			screenY,
			size, 0.7f, 600);

		AnimLoop = false;
		fAnimSpeed = 0.01f;

		if (AnimationCount >= MaxAnimCount - 1)
		{
		
			AnimLoop = true;
			fAnimSpeed = 0.04;
			m_playerState = PlayerState_IDLE;
			AnimationCount = 1;
			MaxAnimCount = 10;
			size.cx = 30;
			size.cy = 25;
			Skill = false;
			m_bmoveable = false;

		}

	}
	else
	{
		
		if (m_bmoveable)
			m_playerDirBitmap[dir][PlayerState_WALK].AnimationUpdate(backDC, AnimationCount,
				screenX,
				screenY,
				size, 2.0f);
		else
			m_playerDirBitmap[dir][PlayerState_IDLE].AnimationUpdate(backDC, AnimationCount,
				screenX,
				screenY, size, 2.0f);
			
	}
	

	



}

void Player::Update(float DeltaTime)
{
	

	if (bHit)
	{
		DieDeltaTime += DeltaTime;
		if (DieDeltaTime > 0.5f)
		{
			bHit = false;
			DieDeltaTime = 0.0f;
		}
	}

	fMoveDeltaTime += DeltaTime;

	if (fMoveDeltaTime > fAnimSpeed)
	{
		//
		if (AnimationCount + 1 >= MaxAnimCount)
		{
			if(AnimLoop)
				AnimationCount = 1;
		}
		else
			AnimationCount++;

		fMoveDeltaTime = 0.0f;
	}
}

void Player::EqupmentAdd(EItem item, bool Equipped) 
{
	if (item == Item_Sword)
	{
		if(Equipped)
			Equipment[0] = item;
		else
			Equipment[0] = None;
		
	}
	else
	{
		Equipment[1] = item;
	}
}

void Player::Reset()
{
}

void Player::Hp_Portion()
{
	// PlayerHP += 1.0f;
	float hp = PlayerHP;
	hp += 1.0f;

	if (hp >= PlayerMaxHP)
	{
		PlayerHP = PlayerMaxHP;
	}
	else
	{
		PlayerHP = hp;
	}
}

void Player::SetPlayerState(PlayerState state)
{
	m_playerState = state;
}

