#pragma once
#ifndef HEADER_H
#define HEADER_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Paddle.h"

using namespace sf;
using namespace std;

/////////////Ball/////////////
class Ball
{
	sf::RenderWindow* window;
	sf::CircleShape circle;
public:
	double deff;
	double koefball;
	double k;
	double x;
	double y;
	double b;
	int count;
	Ball(RenderWindow* window, float time, double koef);
	void updateball(Paddle one, Paddle two);
	void setPos(double x, double y);
	bool isTouch(Paddle pad);
	void drawball();
	bool isTop();
	bool isBot();
};

#endif HEADER_H