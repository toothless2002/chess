#include "board.h"
#include "load_peaces.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
board::board(char*** t, sf::RenderWindow* w) {
    this->table = t;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            std::cout << table[i][j][0] << table[i][j][1] << " ";
        }
        std::cout << std::endl;
    }
    this->window = w;
}
void board::run() {
    sf::RectangleShape** rects = new sf::RectangleShape * [8];
    for (int i = 0; i < 8; i++) {
        rects[i] = new sf::RectangleShape[8];
    }
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            rects[row][col].setSize(sf::Vector2f(100, 100));
            if ((row + col) % 2 == 1)
                rects[row][col].setFillColor(sf::Color(255, 166, 77));
            else
                rects[row][col].setFillColor(sf::Color(255, 242, 230));
            rects[row][col].setPosition(row * 100, col * 100);
        }
    }
    Peaces peaces(table);
    sf::Sprite sprite;
    sf::Image im;
    im.loadFromFile("images/chess_peaces.png");
    sf::Texture tx;
    tx.loadFromImage(im);
    std:: vector <sf::Sprite*> sprites;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (table[i][j][0] != '-') {
            sf::Sprite* sprite = new sf::Sprite;
            sprite->setTexture(*peaces.RetTex(i,j));
            sprite->setScale(0.234, 0.234);
            sprite->setPosition(j * 100, i * 100);
            sprites.push_back(sprite);
            
            }
        }
    }
    while (window->isOpen())
    {
        sf::Event event;
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window->close();
        }

        window->clear();
        for (int row = 0; row < 8; row++) {
            for (int col = 0; col < 8; col++) {
                window->draw(rects[row][col]);
            }
        }
        for (int i = 0; i < sprites.size(); i++)
            window->draw(*sprites[i]);
        window->display();
    }
    for (int i = 0; i < sprites.size(); i++)
        delete sprites[i];
}