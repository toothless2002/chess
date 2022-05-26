#include <SFML/Graphics.hpp>
#include "load_peaces.h"
#include <iostream>
#include "board.h"
sf::Texture* Peaces::RetTex (int i , int j) {
	char n[2] = { table[i][j][0],table[i][j][1] };
	if (n[1] == 'W') {
		if (n[0] == 'Q')
			return(texo[0]);
		if (n[0] == 'K')
			return(texo[1]);
		if (n[0] == 'B')
			return(texo[2]);
		if (n[0] == 'K')
			return(texo[3]);
		if (n[0] == 'R')
			return(texo[4]);
		if (n[0] == 'P')
			return(texo[5]);
	}
	if (n[1] == 'B') {
		if (n[0] == 'Q')
			return(texo[6]);
		if (n[0] == 'K')
			return(texo[7]);
		if (n[0] == 'B')
			return(texo[8]);
		if (n[0] == 'K')
			return(texo[9]);
		if (n[0] == 'R')
			return(texo[10]);
		if (n[0] == 'P')
			return(texo[11]);
	}
}
Peaces::Peaces(char***t) {
	table = t;
	tex = new sf::Texture;
	texo = new  sf::Texture*[12];
	for (int i = 0; i < 12; i++) {
		texo[i] = new sf::Texture;
	}
	image.loadFromFile("images/chess_peaces.png");
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 6; j++) {
			texo[i*6+j]->loadFromImage(image, sf::IntRect(j*426, i*426, 426, 426));
		}
	}
}