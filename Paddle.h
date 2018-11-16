#pragma once
#ifndef PADDLE_H
#define PADDLE_H

#include <SFML/Graphics.hpp>
#include <iostream>

////////////Paddle////////////
using namespace sf;
using namespace std;
class Paddle
{
	sf::RenderWindow* window;
	sf::RectangleShape rectangle;
public:
	double score;
	double y;
	double player;
	Paddle(sf::RenderWindow* window, int player);
	void setY(double &y, float time);
	void update(float time);
	void draw();
};

#endif