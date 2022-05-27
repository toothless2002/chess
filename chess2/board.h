#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "load_peaces.h"
#include "mohre.h"
class board {
public:
	sf::RenderWindow* window;
	std::vector <sf::Sprite*> sprites;
	char*** table;
	mohre*** Ptable;
	Peaces peaces; 
	sf::Mouse mush;
	void run();
	board(char***, sf::RenderWindow*,mohre***);
	void drawpeaces();
	void updatesprite();
	void drawlighter(int, int);
	void drawleftclick(int, int);
};
