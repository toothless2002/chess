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
	sf::Texture* RetTex(int  ,int );
	Peaces(char***);

};