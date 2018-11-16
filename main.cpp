#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <sstream>
#include <vector>
#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <ctime> 
#include "Paddle.h"
#include "Ball.h"
#include "menu.h"
#include "Button.h"


using namespace sf;
using namespace std;

void playhuman(RenderWindow *window, Paddle &one, Paddle &two, Ball &ball, float &time, double koef);
void playbot(RenderWindow *window, Paddle &one, Paddle &two, Ball &ball, float &time, double koef, double difficulty);
bool countscore(Paddle &one, Paddle &two, Ball &ball);
void updatebot(Paddle &two, Ball ball, float time, double difficulty);


int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Pong");
	window.setVerticalSyncEnabled(true);

	Clock clock;
	double difficulty = 0;
	double koef = 0.15;
	float mytime = 16;
	int count = 0;
	int who = 0;

	SoundBuffer shootBuffer;
	shootBuffer.loadFromFile("res//farkassound.ogg");
	Sound shoot(shootBuffer);


	menu(&window, koef, who, difficulty);
	Ball ball(&window, mytime, koef);
	Paddle one(&window, 1);
	Paddle two(&window, 2);

	display(&window, one, two, ball);
	pause();

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
			{
				gamepause(&window, koef, who, difficulty, one, two, ball, mytime, koef);
			}
			if (event.type == sf::Event::Closed) //||
				window.close();
		}
		count++;
		if (one.score == 10 || two.score == 10)
		{
			ggfunc(&window, koef, who, difficulty, one, two, ball, mytime, koef);
		}
		printscore(&window, one, two);
		mytime = clock.getElapsedTime().asMilliseconds();
		clock.restart();
		if (who == 1) { playhuman(&window, one, two, ball, mytime, koef); }
		else if (who == 2) { koef = 0.2; playbot(&window, one, two, ball, mytime, koef, difficulty); }
	}
	return 0;
}


void playhuman(RenderWindow *window, Paddle &one, Paddle &two, Ball &ball, float &time, double koef)
{
	////////////////////
	ball.updateball(one, two);
	one.update(time);
	two.update(time);

	if (countscore(one, two, ball))
	{
		restart(window, one, two, ball, time, koef);
		display(window, one, two, ball);
		pause();
	}
	display(window, one, two, ball);
	////////////////////
}
void playbot(RenderWindow *window, Paddle &one, Paddle &two, Ball &ball, float &time, double koef, double difficulty)
{
	////////////////////
	ball.updateball(one, two);
	one.update(time);
	updatebot(two, ball, time, difficulty);

	if (countscore(one, two, ball))
	{
		restart(window, one, two, ball, time, koef);
		display(window, one, two, ball);
		pause();
	}
	display(window, one, two, ball);
	////////////////////
}
bool countscore(Paddle &one, Paddle &two, Ball &ball)
{
	if (ball.x <= 15)
	{
		two.score += 1;
		return 1;
	}
	else if (ball.x >= 785)
	{
		one.score += 1;
		return 1;
	}
	return 0;
}
void updatebot(Paddle &two, Ball ball, float time, double difficulty)
{
	double y = 0;
	if (ball.x > difficulty)
	{
		y = abs((792 - ball.b) / ball.k);

		if (two.y < y - 30)
		{
			two.y += time * 0.35;
		}
		if (two.y > y + 30)
		{
			two.y -= time * 0.35;
		}
		two.setY(two.y, time);
	}	
}