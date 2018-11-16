#include <SFML/Graphics.hpp>
#include <string>
#include <sstream>
#include <iostream>
#include "Button.h"

using namespace sf;
using namespace std;

/////////////Button/////////////
Button::Button() {}
Button::Button(RenderWindow* window, string filename, Vector2f bPosition, IntRect bSprite, string str) {
	this->bPosition = bPosition;
	this->bSprite = bSprite;
	this->window = window;
	this->color =Color::Blue;
	image.loadFromFile(filename);
	guiTexture.loadFromImage(image);
	sprite.setTexture(guiTexture);
	sprite.setTextureRect(bSprite);
	sprite.setPosition(bPosition);
	sprite.setColor(color);

	ostringstream Title;
	Title << str;
	font.loadFromFile("res//7fonts.ru_REGISTER.ttf");

	this->text.setFont(font);
	this->text.setCharacterSize(32);
	this->text.setString(Title.str());
	this->text.setPosition(bPosition);
}
void Button::ButtonDraw() {
	this->window->draw(this->sprite);
	sprite.setColor(color);
	this->window->draw(this->text);
}
void Button::setColor(Color color)
{
	sprite.setColor(color);
}