#include "Dungeon_Button.h"
#include "Camera.h"
Dungeon_Button::Dungeon_Button(int x, int y, int _ButtonCount, int y0ffset, bool _torchlight, int X0ffset) : Object(x,y)
{
	Torchlight = _torchlight;
	m_BitMap = BitMapManager::GetInstance()->GetBitMap(ImageType_Dungeon_Object);
	m_size = { 31,136 };
	m_ButtonCount = _ButtonCount;
	

	//m_button = new Button[m_ButtonCount];
	
	for (int i = 0; i < m_ButtonCount; i++)
	{
		Button* button = new Button;
		button->button = m_BitMap[Torchlight ? 3 : 1]; // 버튼 이미지 넣음
		button->collision = { 0,0,0,0 };
		button->size = { 16, 16 };
		button->pos = { x + (X0ffset == 0 ? (button->size.cx * 2) : X0ffset * i),y + y0ffset * i};
		m_buttons.push_back(button);
	}
}

Dungeon_Button::~Dungeon_Button()
{
	for (auto button : m_buttons)
	{
		delete button;
	}
}

void Dungeon_Button::Draw(HDC backDC, float DeltaTime)
{
	

	//m_BitMap->AnimationUpdate(backDC, 0, screenX, screenY, m_size, 1.0F);


	for (auto button : m_buttons)
	{
		int screenX = (((WINDOWSIZE_WIDTH / 2) - (button->size.cx * 2)) - Camera::GetInstance()->GetX()) + button->pos.X;
		int screenY = (((WINDOWSIZE_HEIGHT / 2) - (button->size.cy * 2)) - Camera::GetInstance()->GetY()) + button->pos.Y;

		button->button.AnimationUpdate(backDC, button->pressed, screenX, screenY, button->size, 2.0f, button->pressed ? Torchlight ? 16 : 0 : 0);

		button->collision = { screenX, screenY, screenX + m_size.cx, screenY + button->size.cy * 2 };
		//Rectangle(backDC, button->collision.left, button->collision.top,
		//	button->collision.right, button->collision.bottom);
	}

}

void Dungeon_Button::ButtonCollision(RECT rect)
{
	RECT tmp;
	for (int i = 0; i < m_ButtonCount; i++)
	{
		if (IntersectRect(&tmp, &m_buttons[i]->collision, &rect))
		{
			m_buttons[i]->pressed = true;
		}
	}
	
}

bool Dungeon_Button::ButtonCheck()
{
	for (auto button : m_buttons)
	{
		if (!button->pressed)
		{
			return false;
		}
	}


	return true;
}

void Dungeon_Button::Update(float DeltaTime)
{
	for (auto button : m_buttons)
	{
		if (!button->pressed)
		{
			return;
		}
	}

	

}

void Dungeon_Button::Reset()
{
}
