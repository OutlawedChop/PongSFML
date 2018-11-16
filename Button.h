#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>


using namespace sf;
using namespace std;

/////////////Button/////////////
class Button
{
private:
	RenderWindow * window;
	IntRect bSprite;
	Texture guiTexture;
	Image image;

	Font font;
	Vector2f position;
	string str;
	int size;

public:
	Vector2f bPosition;
	Text text;
	Sprite sprite;
	Color color;
	Button(RenderWindow* window, string name, Vector2f bPosition, IntRect bSprite, string text);
	void ButtonDraw();
	void setColor(Color color);
	Button();
};

