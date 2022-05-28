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
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (Ptable[i][j] != NULL) {
                if (Ptable[i][j]->color == 'B' && Ptable[i][j]->typ == 'K')
                    blackking = Ptable[i][j];
                if (Ptable[i][j]->color == 'W' && Ptable[i][j]->typ == 'K')
                    whiteking = Ptable[i][j];
            }
        }
    }
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
                        mate(4, Ptable[leftclicky][leftclickx]);
                        def(4, Ptable[leftclicky][leftclickx]);
                    }
                    else
                        continue;
                }
            }
            drawleftclick(leftclickx, leftclicky);
        }
        
        if (blackking->imchecked()) {
            drawlighterred(blackking->y , blackking->x );
            bool check=true;
            for (int i = 0; i < blacks.size(); i++) {
                if (blacks[i]->p_moves().size() > 0)
                    check= false;
            }
            if(check)
            cout << "b mated";
        }
        if (whiteking->imchecked()) {
            drawlighterred(whiteking->y , whiteking->x );
            bool check = true;
            for (int i = 0; i < whites.size(); i++) {
                if (whites[i]->p_moves().size() > 0)
                    check = false;
            }
            if (check)
            cout << "w mated";
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
void board::drawlighterred(int x, int y) {
    sf::Sprite lighterS;

    lighterS.setTexture(peaces.lighterred);
    lighterS.setPosition(x * 100, y * 100);
    window->draw(lighterS);
}
void board::drawdot(int x, int y) {
    sf::Sprite lighterS;

    lighterS.setTexture(peaces.greendot);
    lighterS.setPosition(x * 100, y * 100);
    window->draw(lighterS);
}
void board::drawgg(int x, int y) {
    sf::Sprite lighterS;

    lighterS.setTexture(peaces.gg);
    lighterS.setPosition(x * 100, y * 100);
    window->draw(lighterS);
}
void board::drawreddot(int x, int y) {
    sf::Sprite lighterS;

    lighterS.setTexture(peaces.reddot);
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
            bool good = false;
            bool bad = false;
            int* f = xy(a[4 + i], a[5 + i]);
            pmoves.push_back(f[0]);
            pmoves.push_back(f[1]);
            for (int j = 0; j < gmoves.size(); j = j + 2) {
                if (f[0] == gmoves[j] && f[1] == gmoves[j + 1]) {
                    good = true;
                    break;
                }
            }
            for (int j = 0; j < bmoves.size(); j = j + 2) {
                if (f[0] == bmoves[j] && f[1] == bmoves[j + 1]) {
                    bad = true;
                    break;
                }
            }
            if (good)
                drawgg(f[1], f[0]);
            else if(bad)
                drawreddot(f[1], f[0]);
            else
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
    updatesprite();
}
bool board::mate(int m,mohre* s) {
    if (m == 1) {
        vector<mohre*>* turncolor;
        if (s->color == 'W')
            turncolor = &blacks;
        else
            turncolor = &whites;
        bool retans = false;
        bool checkmated = true;
        for (int i = 0; i < turncolor->size(); i++) {
            vector <char> v;
            v = (*turncolor)[i]->p_moves();
            if (v.size() > 0) {
                checkmated = false;
            }
        }
        if (!((*turncolor)[0]->imchecked()))
            checkmated = false;
        if (checkmated) {
            retans = true;
        }
        return retans;
    }
    if (m == 3) {
        vector<mohre*>* turncolor;
        if (s->color == 'W')
            turncolor =&blacks;
        else 
            turncolor = &whites;
        bool retans = true;
        int counter = 0;
        int counter2 = 0;
        for (int i = 0; i < turncolor->size(); i++) {
            vector <char> v;
            v = ( * turncolor)[i]->p_moves();
            for (int j = 0; j < v.size(); j = j + 8) {
                char* onemove = new char[8];
                for (int k = 0; k < 8; k++) {
                    onemove[k] = v[j + k];
                }
                (*turncolor)[i]->domove(onemove);
                counter++;
                if (mate(m - 1,s))
                    counter2++;
                (*turncolor)[i]->undomove(onemove);
                delete onemove;
            }
        }
        if (counter == counter2 && counter > 0)
            return true;
        if (counter == counter2 && counter == 0)
            if (((*turncolor)[0]->imchecked()))
                return true;
        return false;
    }
    if (m == 2) {
        vector<mohre*>* turncolor;
        if (s->color == 'B')
            turncolor = &blacks;
        else
            turncolor = &whites;
        bool retans = false;
        for (int i = 0; i < turncolor->size(); i++) {
            vector <char> v;
            v = (*turncolor)[i]->p_moves();
            for (int j = 0; j < v.size(); j = j + 8) {
                char* onemove = new char[8];
                for (int k = 0; k < 8; k++) {
                    onemove[k] = v[j + k];
                }
                (*turncolor)[i]->domove(onemove);
                if (mate(m - 1,s))
                    retans = true;
                (*turncolor)[i]->undomove(onemove);
                delete onemove;

            }
        }
        return retans;
    }
    if (m == 4) {
        gmoves.clear();
        vector <char> v;
        v = s->p_moves();
        int counter = 0;
        vector <char> tans(0);
        for (int j = 0; j < v.size(); j = j + 8) {
            char* onemove = new char[8];
            for (int k = 0; k < 8; k++) {
                onemove[k] = v[j + k];
            }
            s->domove(onemove);
            if (mate(m - 1,s)) {
                counter = counter + 8;
                for (int k = 0; k < 8; k++) {
                    tans.push_back(onemove[k]);
                }
            }
            s->undomove(onemove);
            delete onemove;
        }
        for (int i = 0; i < tans.size(); i = i + 8) {
            int* f = xy(tans[4 + i], tans[5 + i]);
            gmoves.push_back(f[0]);
            gmoves.push_back(f[1]);
            delete f;
        }
        return false;
    }
}
bool board::def(int m, mohre* s) {
    if (m == 0) {
        vector<mohre*>* turncolor;
        if (s->color == 'B')
            turncolor = &blacks;
        else
            turncolor = &whites;
        bool checkmated = true;
        for (int i = 0; i < turncolor->size(); i++) {
            vector <char> v;
            v = (*turncolor)[i]->p_moves();
            if (v.size() > 0) {
                checkmated = false;
            }
        }
        if (!((*turncolor)[0]->imchecked()))
            checkmated = false;
        if (checkmated) {
            return true;
        }
        return false;
    }
    if (m == 1) {
        vector<mohre*>* turncolor;
        if (s->color == 'W')
            turncolor = &blacks;
        else
            turncolor = &whites;
        bool retans = false;
        for (int i = 0; i < turncolor->size(); i++) {
            vector <char> v;
            v = (*turncolor)[i]->p_moves();
            for (int j = 0; j < v.size(); j = j + 8) {
                char* onemove = new char[8];
                for (int k = 0; k < 8; k++) {
                    onemove[k] = v[j + k];
                }
                (*turncolor)[i]->domove(onemove);
                if (def(m - 1,s))
                    retans = true;
                (*turncolor)[i]->undomove(onemove);
                delete onemove;
            }
        }
        return retans;
    }
    if (m == 3) {
        vector<mohre*>* turncolor;
        if (s->color == 'W')
            turncolor = &blacks;
        else
            turncolor = &whites;
        bool retans = false;
        for (int i = 0; i < turncolor->size(); i++) {
            vector <char> v;
            v = (*turncolor)[i]->p_moves();
            for (int j = 0; j < v.size(); j = j + 8) {
                char* onemove = new char[8];
                for (int k = 0; k < 8; k++) {
                    onemove[k] = v[j + k];
                }
                (*turncolor)[i]->domove(onemove);
                if (def(m - 1,s))
                    retans = true;
                (*turncolor)[i]->undomove(onemove);
                delete onemove;
            }
        }
        return retans;
    }
    if (m == 2) {
        vector<mohre*>* turncolor;
        if (s->color == 'B')
            turncolor = &blacks;
        else
            turncolor = &whites;
        int counter = 0;
        int counter2 = 0;
        for (int i = 0; i < turncolor->size(); i++) {
            vector <char> v;
            v = (*turncolor)[i]->p_moves();
            for (int j = 0; j < v.size(); j = j + 8) {
                char* onemove = new char[8];
                for (int k = 0; k < 8; k++) {
                    onemove[k] = v[j + k];
                }
                (*turncolor)[i]->domove(onemove);
                counter++;
                if (def(m - 1,s))
                    counter2++;
                (*turncolor)[i]->undomove(onemove);
                delete onemove;

            }
        }
        if (counter == counter2 && counter > 0)
            return true;
        if (counter == counter2 && counter == 0)
            if ((*turncolor)[0]->imchecked())
                return true;
        return false;
    }
    if (m == 4) {
        bmoves.clear();
        vector <char> v;
        v = s->p_moves();
        int counter = 0;
        vector <char> tans(0);
        for (int j = 0; j < v.size(); j = j + 8) {
            char* onemove = new char[8];
            for (int k = 0; k < 8; k++) {
                onemove[k] = v[j + k];
            }
            s->domove(onemove);
            if (def(m - 1, s)) {
                counter = counter + 8;
                for (int k = 0; k < 8; k++) {
                    tans.push_back(onemove[k]);
                }
            }
            s->undomove(onemove);
            delete onemove;
        }
        for (int i = 0; i < tans.size(); i = i + 8) {
            int* f = xy(tans[4 + i], tans[5 + i]);
            bmoves.push_back(f[0]);
            bmoves.push_back(f[1]);
            delete f;
        }
        return false;
    }
}