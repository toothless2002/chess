#pragma once
#include <SFML/Graphics.hpp>
class board {
public:
	sf::RenderWindow* window;
	char*** table;
	void run();
	board(char***, sf::RenderWindow*);
};
