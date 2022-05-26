#include <iostream>
#include <SFML/Graphics.hpp>
#include "board.h"
int main() {
	sf::RenderWindow window(sf::VideoMode(1000, 800), "Chess", sf::Style::Titlebar | sf::Style::Close);
    char*** table = new char** [8];
    for (int i = 0; i < 8; i++) {
        table[i] = new char* [8];
        for (int j = 0; j < 8; j++) {
            table[i][j] = new char[2];
        }
    }
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            std::cin >> table[i][j][0] >> table[i][j][1];
            std::cin.ignore();
        }
    }
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            std::cout<< table[i][j][0] << table[i][j][1]<<" ";
        }
        std::cout << std::endl;
    }


    board mb(table, &window);
    mb.run();
}