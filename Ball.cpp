#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime> 
#include <windows.h>
#include <cstdlib>
#include "Ball.h"


using namespace sf;
using namespace std;

/////////////Ball/////////////
Ball::Ball(RenderWindow* window, float mytime, double koef)
{
	SYSTEMTIME st;
	GetLocalTime(&st);
	srand(st.wMilliseconds);
	this->k = (double)(rand()) / RAND_MAX * (5 - 1.5) + 1.5;
	if (st.wMilliseconds > 750)
	{
		this->deff = -deff;
		this->k = -k;
		this->b = x - k * y;
	}	
	this->x = 400;
	this->y = 300;
	this->b = x - k * y;
	this->koefball = koef;
	this->deff = mytime * koef;
	this->count = 0;
	this->window = window;
	this->circle.setPosition(x, y);
	this->circle.setRadius(10);
	this->circle.setOrigin(5, 5);
}
void Ball::updateball(Paddle one, Paddle two)
{
	if (isTop())
	{
		this->deff = -deff;
		this->k = -k;
		this->b = x - k * y;
	}
	else if (isBot())
	{
		this->deff = -deff;
		this->k = -k;
		this->b = x - k * y;
	}
	else if (isTouch(one) || isTouch(two))
	{
		this->count += 1;
		this->k = -k;
		this->b = x - k * y;
		if (deff>0)
			this->deff = deff + count * 0.05;
		else
			this->deff = deff - count * 0.05;
	}
	this->y -= deff;
	this->x = k * y + b;
	setPos(x, y);
}
void Ball::setPos(double x, double y)
{
	this->circle.setPosition(x, y);
}
bool Ball::isTouch(Paddle pad)
{
	if (pad.player == 1)
	{
		if (this->x <= 35 && this->y <= pad.y + 50 && this->y >= pad.y - 50)
		{
			return 1;
		}
	}
	else
	{
		if (this->x >= 760 && this->y <= pad.y + 50 && this->y >= pad.y - 50)
		{
			return 1;
		}
	}
	return 0;
}
void Ball::drawball()
{
	this->window->draw(this->circle);
}
bool Ball::isTop()
{
	if (y <= 0)
	{
		return 1;
	}
	return 0;
}
bool Ball::isBot()
{
	if (y >= 590)
	{
		return 1;
	}
	return 0;
}