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

	m_MiniChangeAnimBitmap = BitMapManager::GetInstance()->GetBitMap(ImageType_Player_MiniChange);
	m_MiniBitmap		   = BitMapManager::GetInstance()->GetBitMap(ImageType_PlayerMini);
	m_PlayerFallBitmap     = BitMapManager::GetInstance()->GetBitMap(ImageType_Player_FALL);
	m_ShieldBitmap         = BitMapManager::GetInstance()->GetBitMap(ImageType_Shield);
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

	PlayerMaxHP = PLAYER_DEFAULT_HP;
	PlayerHP = PLAYER_DEFAULT_HP;
}

//976 633
Player::~Player()
{
	
}

void Player::Reset()
{
	PlayerMaxHP = PLAYER_DEFAULT_HP;
	PlayerHP = PLAYER_DEFAULT_HP;
	Equipment[0] = None;
	Equipment[1] = None;
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
		rect.left = player_rect.left - (size.cx);
		rect.right = player_rect.right - (size.cx);
		break;
	case RIGHT:
		rect.left = player_rect.left + (size.cx);
		rect.right = player_rect.right + (size.cx);
		break;
	case UP:
		rect.top = player_rect.top - (size.cy);
		rect.bottom = player_rect.bottom - (size.cy);
		break;
	case DOWN:
		rect.top = player_rect.top + (size.cy);
		rect.bottom = player_rect.bottom + (size.cy);
		break;
	default:
		break;
	}

	GameManager::GetInstance()->FieldObject_AttackCollision(rect);
}

bool Player::PlayerInput(float DeltaTime)
{
	if (MiniChange)
		return false;

	if (m_playerState == PlayerState_FALLWATER || bHit || m_playerState == PlayerState_FALL)
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

	if (GetAsyncKeyState(0x4C) && 0x8000 && Equipment[1] == Item_Shield) // L : 방패
	{
		m_playerState = PlayerState_Shield;
		Skill = true;
		AnimationCount = 1;
		MaxAnimCount = 8;

		size.cx = 200;
		size.cy = 200;
	}

	
	if (m_playerState == PlayerState_Shield)
		return false;

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
		screenX = (((WINDOWSIZE_WIDTH  / 2) - (size.cx / 2)) - Camera::GetInstance()->GetX()) + m_pos.X;
		screenY = (((WINDOWSIZE_HEIGHT / 2) - (size.cy / 2)) - Camera::GetInstance()->GetY()) + m_pos.Y;
	}
	else
	{
		screenX = ((WINDOWSIZE_WIDTH  / 2) - (size.cx * 2)) - Camera::GetInstance()->GetX() + m_pos.X;
		screenY = ((WINDOWSIZE_HEIGHT / 2) - (size.cy * 2)) - Camera::GetInstance()->GetY() + m_pos.Y;
	}

	int AttackX = (((WINDOWSIZE_WIDTH  / 2) - (30 * 2)) - Camera::GetInstance()->GetX()) + m_pos.X;
	int AttackY = (((WINDOWSIZE_HEIGHT / 2) - (25 * 2)) - Camera::GetInstance()->GetY()) + m_pos.Y;

	if (Mini) // 미니 상태 콜리전 변경
		player_rect = { AttackX + 20, AttackY + 20, AttackX + 30 * 2 - 20, AttackY + 25 * 2 };
	else
		player_rect = { AttackX + 10, AttackY, AttackX + 30 * 2 - 10, AttackY + 25 * 2 };
	

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

	switch (m_playerState)
	{
	case PlayerState_IDLE:
	case PlayerState_WALK:
		if (MiniChange) // 미니 체인지 애니메이션 재생 
		{
			m_MiniChangeAnimBitmap->AnimationUpdate(backDC, AnimationCount, screenX, screenY, size, 2.0f);
		}
		else
		{
			if (Mini)
			{
				m_MiniBitmap->AnimationUpdate(backDC, AnimationCount, screenX, screenY, size, 2.0f);
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
		break;
	case PlayerState_FALLWATER:
		if (Mini)
		{
			m_MiniBitmap->AnimationUpdate(backDC, AnimationCount, screenX, screenY, size, 2.0f, 160);
			AnimLoop = false;
			fAnimSpeed = 0.1f;
		}
		else
		{
			m_playerDirBitmap[dir][PlayerState_FALLWATER].AnimationUpdate(backDC, AnimationCount,
				screenX,
				screenY, size, 2.0f);
			AnimLoop = false;
			fAnimSpeed = 0.1f;
		}


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
		break;
	case PlayerState_Attack:
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

		break;
	case PlayerState_HIT:
		AnimLoop = false;
		fAnimSpeed = 0.05f;
		m_playerDirBitmap[dir][PlayerState_HIT].AnimationUpdate(backDC, AnimationCount,
			screenX,
			screenY, size, 2.0f);
		

		// 방향별 뒤로 밀림
		switch (dir)
		{
		case LEFT:
			m_pos.X += 2;
			break;
		case RIGHT:
			m_pos.X -= 2;
			break;
		case UP:
			m_pos.Y += 2;
			break;
		case DOWN:
			m_pos.Y -= 2;
			break;
		default:
			break;
		}
		
		if (AnimationCount >= MaxAnimCount - 1)
		{
			AnimLoop = true;
			fAnimSpeed = 0.04;
			m_playerState = PlayerState_IDLE;
			AnimationCount = 1;
			m_bmoveable = false;

			
		}
		break;
	case PlayerState_Shield:
		m_ShieldBitmap->AnimationUpdate(backDC, 0, screenX, screenY, m_ShieldBitmap->GetSize(), 1.0F);
		m_playerSkillDirBitmap[dir]->AnimationUpdate(backDC, AnimationCount,
			screenX,
			screenY,
			size, 0.7f, 800);

		ShieldCollision = { screenX, screenY, screenX + m_ShieldBitmap->GetSize().cx, screenY + m_ShieldBitmap->GetSize().cy };
		//Rectangle(backDC, ShieldCollision.left, ShieldCollision.top, ShieldCollision.right, ShieldCollision.bottom);
		AnimLoop = false;
		fAnimSpeed = 0.01f;

		if (AnimationCount >= MaxAnimCount - 1)
		{

			AnimLoop = true;
			fAnimSpeed = 0.04;
			m_playerState = PlayerState_IDLE;
			AnimationCount = 1;
			MaxAnimCount = 5;
			size.cx = 30;
			size.cy = 25;
			Skill = false;
			m_bmoveable = false;

		}
		break;
	case PlayerState_PICKUP:
		break;
	case PlayerState_PICKUP_WALK:
		break;
	case PlayerState_PULL:
		break;
	case PlayerState_ROLL:
		break;
	case PlayerState_FALL:
		m_PlayerFallBitmap->AnimationUpdate(backDC, AnimationCount,
			screenX,
			screenY, size, 2.0f);
		AnimLoop = false;
		fAnimSpeed = 0.1f;
		
		if (AnimationCount >= MaxAnimCount - 1)
		{

			switch (dir)
			{
			case LEFT:
				m_pos.X += size.cx * 2;
				break;
			case RIGHT:
				m_pos.X -= size.cx * 2;
				break;
			case UP:
				m_pos.Y += size.cy *2;
				break;
			case DOWN:
				m_pos.Y -= size.cy * 2;
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
		break;
	default:
		break;
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

			if (MiniChange) //미니체인지 애니메이션 종료시
			{
				MiniChange = false;
				Mini = true;
				AnimationCount = 1;
				MaxAnimCount = 6;
				size = { 20,20 };
				fAnimSpeed = 0.1f;
			}
				
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


void Player::MiniReset()
{
	size.cx = 30;
	size.cy = 25;
	Mini = false;
	fAnimSpeed = 0.04f;

	
}

void Player::MiniModeChange(int x, int y)
{
	m_pos.X = x;
	m_pos.Y = y;
	MiniChange = true;
	MaxAnimCount = 20;
}

void Player::DamageHP(float dmage)
{
	if (bHit || m_playerState == PlayerState_Shield)
		return;

	bHit = true;
	AnimationCount = 1;
	PlayerHP -= dmage;
	SetPlayerState(PlayerState_HIT);
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
	if (m_playerState == PlayerState_Shield)
		return;

	if (m_playerState != PlayerState_FALL
		&& m_playerState != PlayerState_FALL)
	{
		m_playerState = state;
		AnimationCount = 0;
	}

	
	
	


}

