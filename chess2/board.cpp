#include "board.h"
#include "load_peaces.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

board::board(char*** t, sf::RenderWindow*w ,mohre*** pt,char b):peaces(t) {
    this->table = t;
    this->turn = b;
    this->Ptable = pt;
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
        leftclick = false;
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
                if (x >= 0 && x < 8 && y >= 0 && y < 8) {
                    //lighterstatus = false;
                    leftclick = true;
                    leftclickx = x;
                    leftclicky = y;
                    //std::cout << x << "   " << y << std::endl;
                }

            }
            
        }
        

        for (int row = 0; row < 8; row++) {
            for (int col = 0; col < 8; col++) {
                window->draw(rects[row][col]);
            }
        }


        drawpeaces();
        
        if (mush.getPosition(*window).x >= 0 && mush.getPosition(*window).y >= 0 &&
            mush.getPosition(*window).x < 800 && mush.getPosition(*window).y < 800) {
                {
                    if (lighterstatus) {
                        drawlighter(x, y);

                    }
                }
        }
        if (leftclick||firstclicks) {
            if (firstclicks == true && leftclick) {
                if (firstclickx == leftclickx && firstclicky == leftclicky) {
                    firstclicks = false;
                    continue;
                }
                bool flag = false;
                for (int i = 0; i < pmoves.size(); i=i+2) {
                    if (leftclicky == pmoves[i] && leftclickx == pmoves[i+1]) {
                        flag = true;
                        cout << leftclickx << " " << leftclicky << endl;
                    }
                }
                if (flag) {
                move(firstclickx, firstclicky, leftclickx, leftclicky);
                turn = (turn == 'W') ? 'B' : 'W';
               // cout << firstclickx << " " << firstclicky << " " << leftclickx << " " << leftclicky << endl;
                }
                firstclicks = false;
                continue;
            }
            if (firstclicks == false) {
                if (Ptable[leftclicky][leftclickx] != NULL ) {
                    if (Ptable[leftclicky][leftclickx]->color == turn) {
                        firstclickx = leftclickx;
                        firstclicky = leftclicky;
                        firstclicks = true;
                    }
                    else
                        continue;
                }
            }
            drawleftclick(leftclickx, leftclicky);
        }
        
        

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
    sprites.clear();
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
void board::drawdot(int x, int y) {
    sf::Sprite lighterS;

    lighterS.setTexture(peaces.greendot);
    lighterS.setPosition(x * 100, y * 100);
    window->draw(lighterS);
}
void board::drawleftclick(int x, int y) {
    sf::Sprite lighterS;
    std::vector<char>a;
    pmoves.clear();
    if (Ptable[y][x] != NULL) {
        a = Ptable[y][x]->p_moves();
        for (int i = 0; i < a.size(); i = i + 8) {
            int* f = xy(a[4 + i], a[5 + i]);
            pmoves.push_back(f[0]);
            pmoves.push_back(f[1]);

            drawdot(f[1], f[0]);
            delete f;
        }
    }
    
    lighterS.setTexture(peaces.leftclick);
    lighterS.setPosition(x * 100, y * 100);
    window->draw(lighterS);
}
void board::move(int a, int b, int x, int y) {
    Ptable[y][x] = NULL;
    table[y][x][0] = table[b][a][0];
    table[y][x][1] = table[b][a][1];
    table[b][a][0] = '-';
    table[b][a][1] = '-';
    Ptable[y][x] = Ptable[b][a];
    Ptable[y][x]->x = y;
    Ptable[y][x]->y = x;
    Ptable[b][a] = NULL;
    //cout << Ptable[b][a]->x << Ptable[b][a]->y;
    updatesprite();
}
