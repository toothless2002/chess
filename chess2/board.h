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
	char turn;
	vector<int> pmoves;
	vector<int> gmoves;
	vector<int> bmoves;
	mohre* whiteking;
	mohre* blackking;
	void run();
	board(char***, sf::RenderWindow*,mohre***,char);
	void drawpeaces();
	void updatesprite();
	void drawlighter(int, int);
	void drawlighterred(int, int);
	void drawdot(int, int);
	void drawreddot(int, int);
	void drawgg(int, int);
	void drawleftclick(int, int);
	void move(int, int, int, int);
	bool mate(int,mohre*);
	bool def(int, mohre*);
};
