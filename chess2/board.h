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
	int firstclickx ,firstclicky;
	bool firstclicks;
	void run();
	board(char***, sf::RenderWindow*,mohre***);
	void drawpeaces();
	void updatesprite();
	void drawlighter(int, int);
	void drawdot(int, int);
	void drawleftclick(int, int);
	void move(int, int, int, int);
};
