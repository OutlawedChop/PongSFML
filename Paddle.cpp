#include <SFML/Graphics.hpp>
#include "Paddle.h"
#include <iostream>

using namespace sf;
using namespace std;

////////////Paddle////////////
Paddle::Paddle(sf::RenderWindow* window, int player)
{
	this->score = 0;
	this->y = 300;
	this->player = player;
	this->window = window;
	this->rectangle.setSize(sf::Vector2f(10, 100));
	this->rectangle.setOrigin(5, 50);
	if (this->player == 1) 
	{
		this->rectangle.setPosition(25, this->y);
	}
	else 
	{
		this->rectangle.setPosition(775, this->y);
	}
}
void Paddle::setY(double &y, float time)
{
	if (this->player == 1)
	{
		if (y < 50)
		{
			this->y += time * 0.35;
		}
		else if (y > 555)
		{
			this->y -= time * 0.35;
		}
		rectangle.setPosition(25, y);
	}
	else
	{
		if (y < 50)
		{
			rectangle.setPosition(25, y);
			this->y += time * 0.35;
		}
		else if (y > 555)
		{
			this->y -= time * 0.35;
		}
		rectangle.setPosition(775, y);
	}
}
void Paddle::update(float time)
{
	if (this->player == 1) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			this->y -= time * 0.35;
			this->setY(this->y, time);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			this->y += time * 0.35;
			this->setY(this->y, time);
		}
	}
	else {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			this->y -= time * 0.35;
			this->setY(this->y, time);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			this->y += time * 0.35;
			this->setY(this->y, time);
		}
	}
}
void Paddle::draw()
{
	this->window->draw(this->rectangle);
}