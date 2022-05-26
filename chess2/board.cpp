#include "board.h"
#include "load_peaces.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

board::board(char*** t, sf::RenderWindow* w):peaces(t) {
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
    window->setFramerateLimit(90);
    updatesprite();
    bool lighterstatus = false;
    bool leftclick = false;
 
    int leftclickx= 0, leftclicky=0;
    while (window->isOpen())
    {
        sf::Event event;
        window->clear();
        int x = mush.getPosition(*window).x / 100;
        int y = mush.getPosition(*window).y / 100;
        //leftclick = false;
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window->close();
            if (event.type == sf::Event::LostFocus) {
                lighterstatus = false;
                std::cout << "lost" << std::endl;
            }
            if (event.type == sf::Event::GainedFocus) {
                lighterstatus = true;
                std::cout << "gained" << std::endl;
            }
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                //lighterstatus = false;
                leftclick = true;
                leftclickx = x;
                leftclicky = y;
                std::cout << x << "   " << y << std::endl;

            }
        }
        

        for (int row = 0; row < 8; row++) {
            for (int col = 0; col < 8; col++) {
                window->draw(rects[row][col]);
            }
        }


        
        if (mush.getPosition(*window).x >= 0 && mush.getPosition(*window).y >= 0 &&
            mush.getPosition(*window).x < 800 && mush.getPosition(*window).y < 800) {
                {
                    if (lighterstatus) {
                        drawlighter(x, y);

                    }
                    if (leftclick) {
                        drawleftclick(leftclickx, leftclicky);
                    }
                }
        }
        
        

        drawpeaces();
        window->display();
    }
    
}
void board::drawpeaces() {
    for (int i = 0; i < sprites.size(); i++)
        window->draw(*sprites[i]);
}
void board::updatesprite() {
    for (int i = 0; i < sprites.size(); i++)
        delete sprites[i];
    
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (table[i][j][0] != '-') {
                sf::Sprite* sprite = new sf::Sprite;
                sprite->setTexture(*peaces.RetTex(i, j));
                sprite->setScale(0.234, 0.234);
                sprite->setPosition(j * 100, i * 100);
                sprites.push_back(sprite);

            }
        }
    }
}
void board::drawlighter(int x, int y) {
    sf::Sprite lighterS;
    
    lighterS.setTexture(peaces.lighter);
    lighterS.setPosition(x * 100, y * 100);
    window->draw(lighterS);
}
void board::drawleftclick(int x, int y) {
    sf::Sprite lighterS;

    lighterS.setTexture(peaces.leftclick);
    lighterS.setPosition(x * 100, y * 100);
    window->draw(lighterS);
}