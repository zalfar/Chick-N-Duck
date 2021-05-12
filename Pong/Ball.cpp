#include "Ball.h"

void Ball::init()
{
	w = h = 20; // ukuran bola
	posX = 400; posY = 300; //posisi bola

	ServeTo(Player::Side_Left); //untuk pertama kali bola mengarah ke kiri
}

void Ball::Move() //pergerakan bola
{
	if (((posY + dy) < 100) || ((posY + dy) > 590))
	{
		dy = -dy;
	}

	posX += dx;
	posY += dy;
}

void Ball::PlayerReturns()
{
	dx = -dx;
	posX += dx;
	posY += dy;
}

Player::Side Ball::IsGoingTo() //jika bola mengenai paddle dan arah bola selanjutnya
{
	if (dx > 0) return Player::Side_Right;

	return Player::Side_Left;
}


bool Ball::IsOutOfBounds() //jika bola keluar dari batasan
{
	return (((posX + dx) < 0) || ((posX + dx) > 800));
}

Player::Side Ball::OutOfBoundsSide() //batas bola
{
	if (posX <= 0) return Player::Side_Left;
	if (posX >= 600) return Player::Side_Right;

	return Player::Side_Undefined;
}

void Ball::ServeTo(Player::Side serveTo) //mengarahkan bola
{
	if (serveTo == Player::Side_Left)
	{
		dx = -5;
		dy = -5;
	}

	if (serveTo == Player::Side_Right)
	{
		dx = 5;
		dy = -5;
	}

	dx /= 1;
	dy /= 1;
}