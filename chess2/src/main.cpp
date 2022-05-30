#include <iostream>
#include <SFML/Graphics.hpp>
#include "board.h"
#include <vector>
#include "mohre.h"
//bakcup table ptable turn blacks whites
using namespace std;
int main() {
	sf::RenderWindow window(sf::VideoMode(1000, 800), "Chess", sf::Style::Titlebar | sf::Style::Close);
    char*** table = new char** [8];
    for (int i = 0; i < 8; i++) {
        table[i] = new char* [8];
        for (int j = 0; j < 8; j++) {
            table[i][j] = new char[2];
        }
    }
    mohre*** Ptable = new mohre**[8];
    for (int i = 0; i < 8; i++) {
        Ptable[i] = new mohre* [8];
        for (int j = 0; j < 8; j++) {
            Ptable[i][j] = NULL;
        }
    }
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            std::cin >> table[i][j][0] >> table[i][j][1];
            if (table[i][j][0] == 'K' && table[i][j][1] == 'B')
                blacks.push_back(new king(table[i][j][1], 'K', table, i, j));
            else if (table[i][j][0] == 'P' && table[i][j][1] == 'B')
                blacks.push_back(new pawn(table[i][j][1], 'P', table, i, j));
            else if (table[i][j][0] == 'Q' && table[i][j][1] == 'B')
                blacks.push_back(new queen(table[i][j][1], 'Q', table, i, j));
            else if (table[i][j][0] == 'B' && table[i][j][1] == 'B')
                blacks.push_back(new bishop(table[i][j][1], 'B', table, i, j));
            else if (table[i][j][0] == 'N' && table[i][j][1] == 'B')
                blacks.push_back(new knight(table[i][j][1], 'N', table, i, j));
            else if (table[i][j][0] == 'R' && table[i][j][1] == 'B')
                blacks.push_back(new rook(table[i][j][1], 'R', table, i, j));
            else if (table[i][j][0] == 'K' && table[i][j][1] == 'W')
                whites.push_back(new king(table[i][j][1], 'K', table, i, j));
            else if (table[i][j][0] == 'P' && table[i][j][1] == 'W')
                whites.push_back(new pawn(table[i][j][1], 'P', table, i, j));
            else if (table[i][j][0] == 'Q' && table[i][j][1] == 'W')
                whites.push_back(new queen(table[i][j][1], 'Q', table, i, j));
            else if (table[i][j][0] == 'B' && table[i][j][1] == 'W')
                whites.push_back(new bishop(table[i][j][1], 'B', table, i, j));
            else if (table[i][j][0] == 'N' && table[i][j][1] == 'W')
                whites.push_back(new knight(table[i][j][1], 'N', table, i, j));
            else if (table[i][j][0] == 'R' && table[i][j][1] == 'W')
                whites.push_back(new rook(table[i][j][1], 'R', table, i, j));
            std::cin.ignore();
        }
    }
    for (int i = 0; i < blacks.size(); i++) {
        Ptable[blacks[i]->x][blacks[i]->y] = blacks[i];
    }
    for (int i = 0; i < whites.size(); i++) {
        Ptable[whites[i]->x][whites[i]->y] = whites[i];
    }



    board mb(table, &window,Ptable,'W');
    mb.run();
}