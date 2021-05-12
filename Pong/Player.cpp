#include "Player.h"
#include <assert.h>
#include <windows.h>


void Player::init()
{
	w = 10; //ukuran lebar paddle 
	h = 80; //ukuran tinggi paddle

	posX = 0; //letak paddle
	posY = 220;

	speed = 10; //kecepatan pergerakan paddle
}

void Player::Move()
{
	assert(mySide != Side_Undefined);

	float delta = 0;

	if(mySide == Side_Left)
	{		
		if(GetAsyncKeyState('W') != 0) //inputan keyboard untuk mengendalikan paddle kiri ke atas
		{
			delta -= speed;
		}

		if(GetAsyncKeyState('S') != 0) //inputan keyboard untuk mengendalikan paddle kiri ke bawah
		{
			delta += speed;
		}
	}

	if(mySide == Side_Right)
	{
		if(GetAsyncKeyState(VK_UP) != 0) //inputan keyboard untuk mengendalikan paddle kanan ke atas
		{
			delta -= speed;
		}

		if(GetAsyncKeyState(VK_DOWN) != 0) //inputan keyboard untuk mengendalikan paddle kanan ke bawah
		{
			delta += speed;
		}
	}

	if(( posY + delta > 100) && ((posY + delta) < (600 - h )))
	{
		posY += delta;
	}
}

void Player::SetSide(Side eSide)
{
	mySide = eSide;

	if(mySide == Side_Left)
	{
		posX = 30; //posisi paddle di sisi kiri
	}

	if(mySide == Side_Right)
	{
		posX = 760; //posisi paddle di sisi kanan
	}
}
