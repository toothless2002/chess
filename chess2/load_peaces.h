#pragma once
#include <SFML/Graphics.hpp>

class Peaces {
public:
	char*** table;
	sf::Texture *tex;
	sf::Texture** texo;
	sf::Image image;
	sf::Image lighter_image;
	sf::Texture lighter;
	sf::Image leftclick_image;
	sf::Texture leftclick;
	sf::Texture* RetTex(int  ,int );
	Peaces(char***);

};