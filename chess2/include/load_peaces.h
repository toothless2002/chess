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
	sf::Image lighterred_image;
	sf::Texture lighterred;
	sf::Image leftclick_image;
	sf::Texture leftclick;
	sf::Image greendot_image;
	sf::Texture greendot;
	sf::Image reddot_image;
	sf::Texture reddot;
	sf::Image gg_image;
	sf::Texture gg;
	sf::Font font;
	sf::Font font2;
	sf::Texture* RetTex(int  ,int );
	Peaces(char***);

};