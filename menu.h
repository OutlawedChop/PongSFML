#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <sstream>
#include <vector>
#include <iostream>
#include "Button.h"

using namespace sf;
using namespace std;

void drawButtons(RenderWindow* window, vector<Button> &buttons, Sprite wallSprite);
void choosedifficulty(RenderWindow *window, double &koefball, double &difficulty);
void whotoplaywith(RenderWindow *window, double &koefball, int &who, double &difficulty);
void printscore(RenderWindow* window, Paddle one, Paddle two);
void restart(RenderWindow *window, Paddle &one, Paddle &two, Ball &ball, float &time, double koef);
void display(RenderWindow *window, Paddle &one, Paddle &two, Ball &ball);
void ggfunc(RenderWindow* window, double &koefball, int &who, double &difficulty, Paddle &one, Paddle &two, Ball &ball, float &mytime, double koef);
void gamepause(RenderWindow* window, double &koefball, int &who, double &difficulty, Paddle &one, Paddle &two, Ball &ball, float &mytime, double koef);
void settings(RenderWindow* window, double &koefball, int &who, double &difficulty);
void pause();

void menu(RenderWindow* window, double &koefball, int &who, double &difficulty)
{
	Sprite wallSprite;
	Texture wallTexture;
	wallTexture.loadFromFile("res\\wallpaper.jpg");
	wallSprite.setTexture(wallTexture);

	string filename = "res\\18.png";
	vector<Button> buttons;
	int menuNum = 0;
	bool isMenu = 1;

	Button b1(window, filename, Vector2f(299, 210), IntRect(113, 83, 203, 51), "   Play");
	Button b2(window, filename, Vector2f(299, 280), IntRect(113, 83, 203, 51), " Settings");
	Button b3(window, filename, Vector2f(299, 350), IntRect(113, 83, 203, 51), "   Exit");

	buttons.push_back(b1);
	buttons.push_back(b2);
	buttons.push_back(b3);

	while (isMenu)
	{

		///////////////////////////////////
		sf::Event event;
		window->pollEvent(event);
		if (/*event.type == sf::Event::Closed ||*/
			(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
		{
			window->close();
			isMenu = 0;
		}
		///////////////////////////////////
		if (IntRect(299, 210, 203, 51).contains(Mouse::getPosition(*window))) { buttons[0].setColor(Color::Green); menuNum = 1; }
		else if (IntRect(299, 280, 203, 51).contains(Mouse::getPosition(*window))) { buttons[1].setColor(Color::Green); menuNum = 2; }
		else if (IntRect(299, 350, 203, 51).contains(Mouse::getPosition(*window))) { buttons[2].setColor(Color::Green); menuNum = 3; }
		else { menuNum = 0; }

		drawButtons(window, buttons, wallSprite);
		window->pollEvent(event);
		if (event.type == Event::MouseButtonReleased)
		{
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				if (menuNum == 1) {
					isMenu = 0; 
					whotoplaywith(window, koefball, who, difficulty); }
				if (menuNum == 2) { isMenu = 0; settings(window, koefball, who, difficulty); }
				if (menuNum == 3) { isMenu = 0; window->close(); }
			}
		}
		buttons[0].setColor(Color::Cyan);
		buttons[1].setColor(Color::Cyan);
		buttons[2].setColor(Color::Cyan);
	}
}
void printscore(RenderWindow* window, Paddle one, Paddle two)
{
	Text text1, text2;
	Font font;
	font.loadFromFile("res//7fonts.ru_REGISTER.ttf");

	ostringstream ScoreOne;
	ScoreOne << one.score;

	text1.setFont(font);
	text1.setCharacterSize(40);
	text1.setString(ScoreOne.str());
	text1.setPosition(300, 30);

	ostringstream ScoreTwo;
	ScoreTwo << two.score;

	text2.setFont(font);
	text2.setCharacterSize(40);
	text2.setString(ScoreTwo.str());
	text2.setPosition(460, 30);

	window->draw(text1);
	window->draw(text2);
}
void whotoplaywith(RenderWindow *window, double &koefball, int &who, double &difficulty)
{
	Sprite wallSprite;
	Texture wallTexture;
	wallTexture.loadFromFile("res\\wallpaper.jpg");
	wallSprite.setTexture(wallTexture);


	string filename = "res\\18.png";
	vector<Button> buttons;
	int menuNum = 0;
	bool isMenu = 1;

	Button b1(window, filename, Vector2f(299, 210), IntRect(113, 83, 203, 51), "Player vs Player");
	Button b2(window, filename, Vector2f(299, 280), IntRect(113, 83, 203, 51), "  Player vs Bot");
	Button b3(window, filename, Vector2f(299, 350), IntRect(113, 83, 203, 51), "      Back");
	
	buttons.push_back(b1);
	buttons.push_back(b2);
	buttons.push_back(b3);
	for (int i = 0; i < buttons.size(); i++)
	{
		buttons[i].text.setCharacterSize(18);
		buttons[i].text.setPosition(buttons[i].bPosition.x, buttons[i].bPosition.y + 15);
	}
	
	while (isMenu)
	{
		///////////////////////////////////
		sf::Event event;
		window->pollEvent(event);
		if (/*event.type == sf::Event::Closed ||*/
			(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
		{
			window->close();
			isMenu = 0;
		}
		///////////////////////////////////
		if (IntRect(299, 210, 203, 51).contains(Mouse::getPosition(*window))) { buttons[0].setColor(Color::Green); menuNum = 1; }
		else if (IntRect(299, 280, 203, 51).contains(Mouse::getPosition(*window))) { buttons[1].setColor(Color::Green); menuNum = 2; }
		else if (IntRect(299, 350, 203, 51).contains(Mouse::getPosition(*window))) { buttons[2].setColor(Color::Green); menuNum = 3; }
		else { menuNum = 0; }

		drawButtons(window, buttons, wallSprite);

		window->pollEvent(event);
		if (event.type == Event::MouseButtonReleased)
		{
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				if (menuNum == 1) { isMenu = 0; who = 1; choosedifficulty(window, koefball, difficulty); }
				if (menuNum == 2) { isMenu = 0; who = 2; choosedifficulty(window, koefball, difficulty); }
				if (menuNum == 3) { isMenu = 0; menu(window, koefball, who, difficulty); }
			}
		}
		buttons[0].setColor(Color::Cyan);
		buttons[1].setColor(Color::Cyan);
		buttons[2].setColor(Color::Cyan);
	}
}
void drawButtons(RenderWindow *window, vector<Button> &buttons, Sprite wallSprite)
{
	window->clear();
	window->draw(wallSprite);
	for (int i = 0; i < buttons.size(); i++) {
		buttons[i].ButtonDraw();
	}
	window->display();
}
void choosedifficulty(RenderWindow *window, double &koefball, double &difficulty)
{
	Sprite wallSprite;
	Texture wallTexture;
	wallTexture.loadFromFile("res\\wallpaper.jpg");
	wallSprite.setTexture(wallTexture);

	string filename = "res\\18.png";
	vector<Button> buttons;
	int menuNum = 0;
	bool isMenu = 1;

	Button b1(window, filename, Vector2f(299, 210), IntRect(113, 83, 203, 51), "   Easy");
	Button b2(window, filename, Vector2f(299, 280), IntRect(113, 83, 203, 51), "  Medium");
	Button b3(window, filename, Vector2f(299, 350), IntRect(113, 83, 203, 51), "   Hard");
	buttons.push_back(b1);
	buttons.push_back(b2);
	buttons.push_back(b3);

	while (isMenu)
	{
		///////////////////////////////////
		sf::Event event;
		window->pollEvent(event);
		if (/*event.type == sf::Event::Closed ||*/
			(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
		{
			window->close();
			isMenu = 0;
		}
		///////////////////////////////////
		if	(IntRect(299, 210, 203, 51).contains(Mouse::getPosition(*window))) { buttons[0].setColor(Color::Green); menuNum = 1; }
		else if (IntRect(299, 280, 203, 51).contains(Mouse::getPosition(*window))) { buttons[1].setColor(Color::Green); menuNum = 2; }
		else if (IntRect(299, 350, 203, 51).contains(Mouse::getPosition(*window))) { buttons[2].setColor(Color::Green); menuNum = 3; }
		else { menuNum = 0; }

		drawButtons(window, buttons, wallSprite);
		window->pollEvent(event);
		if (event.type == Event::MouseButtonReleased)
		{
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				if (menuNum == 1) { koefball = 0.15; difficulty = 400; isMenu = 0; }
				if (menuNum == 2) { koefball = 0.20; difficulty = 200; isMenu = 0; }
				if (menuNum == 3) { koefball = 0.25; difficulty = 0; isMenu = 0; }
			}
		}
		buttons[0].setColor(Color::Cyan);
		buttons[1].setColor(Color::Cyan);
		buttons[2].setColor(Color::Cyan);
	}
}
void gamepause(RenderWindow* window, double &koefball, int &who, double &difficulty, Paddle &one, Paddle &two, Ball &ball, float &mytime, double koef)
{
	Sprite wallSprite;
	Texture wallTexture;
	wallTexture.loadFromFile("res\\wallpaper.jpg");
	wallSprite.setTexture(wallTexture);

	string filename = "res\\18.png";
	vector<Button> buttons;
	int menuNum = 0;
	bool isMenu = 1;

	Button b1(window, filename, Vector2f(299, 210), IntRect(113, 83, 203, 51), " Continue");
	Button b2(window, filename, Vector2f(299, 280), IntRect(113, 83, 203, 51), "  Restart");
	Button b3(window, filename, Vector2f(299, 350), IntRect(113, 83, 203, 51), " Main memu");

	buttons.push_back(b1);
	buttons.push_back(b2);
	buttons.push_back(b3);

	for (int i = 0; i < buttons.size(); i++)
	{
		buttons[i].text.setCharacterSize(30);
		buttons[i].text.setPosition(buttons[i].bPosition.x, buttons[i].bPosition.y + 10);
	}


	while (isMenu)
	{

		///////////////////////////////////
		sf::Event event;
		window->pollEvent(event);
		if (/*event.type == sf::Event::Closed ||*/
			(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
		{
			window->close();
			isMenu = 0;
		}
		///////////////////////////////////
		if (IntRect(299, 210, 203, 51).contains(Mouse::getPosition(*window))) { buttons[0].setColor(Color::Green); menuNum = 1; }
		else if (IntRect(299, 280, 203, 51).contains(Mouse::getPosition(*window))) { buttons[1].setColor(Color::Green); menuNum = 2; }
		else if (IntRect(299, 350, 203, 51).contains(Mouse::getPosition(*window))) { buttons[2].setColor(Color::Green); menuNum = 3; }
		else { menuNum = 0; }

		drawButtons(window, buttons, wallSprite);
		window->pollEvent(event);
		if (event.type == Event::MouseButtonReleased)
		{
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				if (menuNum == 1) { 
					isMenu = 0; 
				}
				if (menuNum == 2) {
					isMenu = 0;		
					restart(window, one, two, ball, mytime, koef);
					one.score = 0;
					two.score = 0;
					display(window, one, two, ball);
					pause();
				}
				if (menuNum == 3) {
					isMenu = 0; 
					restart(window, one, two, ball, mytime, koef);
					one.score = 0;
					two.score = 0;
					menu(window, koefball, who, difficulty);
					display(window, one, two, ball);
					pause();
				}
			}
		}
		buttons[0].setColor(Color::Cyan);
		buttons[1].setColor(Color::Cyan);
		buttons[2].setColor(Color::Cyan);
	}
}
void restart(RenderWindow *window, Paddle &one, Paddle &two, Ball &ball, float &mytime, double koef)
{
	double score1, score2;
	score1 = one.score;
	score2 = two.score;
	Ball Nball(window, mytime, koef);
	Paddle None(window, 1);
	Paddle Ntwo(window, 2);
	ball = Nball;

	SYSTEMTIME st;
	GetLocalTime(&st);
	srand(st.wMilliseconds);
	ball.k = (double)(rand()) / RAND_MAX * (5 - 1.5) + 1.5;
	if (st.wMilliseconds > 750)
	{
		ball.deff = -ball.deff;
		ball.k = -ball.k;
		ball.b = ball.x - ball.k * ball.y;
	}
	one = None;
	two = Ntwo;
	one.score = score1;
	two.score = score2;
}
void display(RenderWindow *window, Paddle &one, Paddle &two, Ball &ball)
{
	window->clear();
	one.draw();
	two.draw();
	ball.drawball();
	printscore(window, one, two);
	window->display();
}
void pause()
{
	Clock clock;
	float time;
	do
	{
		time = clock.getElapsedTime().asSeconds();
	} while (time <= 1);
	Clock restart();
}
void ggfunc(RenderWindow* window, double &koefball, int &who, double &difficulty, Paddle &one, Paddle &two, Ball &ball, float &mytime, double koef)
{
	Text text;
	string str;
	Font font;
	font.loadFromFile("res//7fonts.ru_REGISTER.ttf");
	if (one.score == 10)
	{
		str = "First player won!";
	}
	if (two.score == 10)
	{
		str = "Second player won!" ;
	}

	ostringstream Title;
	Title << str;
	text.setFont(font);
	text.setCharacterSize(32);
	text.setString(Title.str());
	text.setPosition(220, 120);

	string filename = "res\\18.png";
	vector<Button> buttons;
	int menuNum = 0;
	bool isMenu = 1;

	Button b1(window, filename, Vector2f(299, 210), IntRect(113, 83, 203, 51), "  Restart");
	Button b2(window, filename, Vector2f(299, 280), IntRect(113, 83, 203, 51), " Main menu");

	buttons.push_back(b1);
	buttons.push_back(b2);

	for (int i = 0; i < buttons.size(); i++)
	{
		buttons[i].text.setCharacterSize(30);
		buttons[i].text.setPosition(buttons[i].bPosition.x, buttons[i].bPosition.y + 10);
	}
	while (isMenu)
	{
		///////////////////////////////////
		sf::Event event;
		window->pollEvent(event);
		if (/*event.type == sf::Event::Closed ||*/
			(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
		{
			window->close();
			isMenu = 0;
		}
		///////////////////////////////////

		if (IntRect(299, 210, 203, 51).contains(Mouse::getPosition(*window))) { buttons[0].setColor(Color::Green); menuNum = 1; }
		else if (IntRect(299, 280, 203, 51).contains(Mouse::getPosition(*window))) { buttons[1].setColor(Color::Green); menuNum = 2; }
		else { menuNum = 0; }

		window->clear();
		window->draw(text);
		one.draw();
		two.draw();
		ball.drawball();
		printscore(window, one, two);
		for (int i = 0; i < buttons.size(); i++) {
			buttons[i].ButtonDraw();
		}
		window->display();

		window->pollEvent(event);
		if (event.type == Event::MouseButtonReleased)
		{
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				if (menuNum == 1) {
					isMenu = 0;
					restart(window, one, two, ball, mytime, koef);
					one.score = 0;
					two.score = 0;
					display(window, one, two, ball);
					pause();
				}
				if (menuNum == 2) {
					isMenu = 0;
					isMenu = 0;
					restart(window, one, two, ball, mytime, koef);
					one.score = 0;
					two.score = 0;
					menu(window, koefball, who, difficulty);
					display(window, one, two, ball);
					pause();
				}
			}
		}
		buttons[0].setColor(Color::Cyan);
		buttons[1].setColor(Color::Cyan);
	}
}
void settings(RenderWindow* window, double &koefball, int &who, double &difficulty)
{
	Sprite Farkas;
	Texture wallTexture;
	wallTexture.loadFromFile("res\\������_�������.png");
	Farkas.setTexture(wallTexture);


	Text text;
	Font font;
	string str = "You are not welcome here!";
	font.loadFromFile("res//7fonts.ru_REGISTER.ttf");

	//SoundBuffer shootBuffer;
	//shootBuffer.loadFromFile("res//farkassound.ogg");
	//Sound shoot(shootBuffer);

	ostringstream Title;
	Title << str;

	text.setFont(font);
	text.setCharacterSize(26);
	text.setString(Title.str());
	text.setPosition(345, 100);

	string filename = "res\\18.png";
	vector<Button> buttons;
	int menuNum = 0;
	bool isMenu = 1;

	Button b1(window, filename, Vector2f(569, 510), IntRect(113, 83, 203, 51), "   Back");
	buttons.push_back(b1);

	Music music;
	music.openFromFile("res//farkassound.ogg");
	music.play();
	while (isMenu)
	{

		///////////////////////////////////
		sf::Event event;
		window->pollEvent(event);
		if (/*event.type == sf::Event::Closed ||*/
			(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
		{
			window->close();
			isMenu = 0;
		}
		///////////////////////////////////
		if (IntRect(569, 510, 203, 51).contains(Mouse::getPosition(*window))) { buttons[0].setColor(Color::Green); menuNum = 1; }
		else { menuNum = 0; }



		window->clear();
		window->draw(Farkas);
		window->draw(text);
		buttons[0].ButtonDraw();
		window->display();

		window->pollEvent(event);
		if (event.type == Event::MouseButtonReleased)
		{
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				if (menuNum == 1) { isMenu = 0; music.stop(); menu(window, koefball, who, difficulty); }
			}
		}
		buttons[0].setColor(Color::Cyan);
	}
}