#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "load_peaces.h"
class board {
public:
	sf::RenderWindow* window;
	std::vector <sf::Sprite*> sprites;
	char*** table;
	Peaces peaces; 
	sf::Mouse mush;
	void run();
	board(char***, sf::RenderWindow*);
	void drawpeaces();
	void updatesprite();
	void drawlighter(int, int);
	void drawleftclick(int, int);
};
