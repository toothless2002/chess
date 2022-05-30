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
    //backuping 
    backup_table = new char** [8];
    for (int i = 0; i < 8; i++) {
        backup_table[i] = new char* [8];
        for (int j = 0; j < 8; j++) {
            backup_table[i][j] = new char[2];
            for (int k = 0; k < 2; k++) {
                backup_table[i][j][k] = table[i][j][k];
            }
        }
    }
    
    backup_blacks.clear();
    for (int i = 0; i < blacks.size(); i++) {
        if (blacks[i]->color == 'B' && blacks[i]->typ == 'P')
            backup_blacks.push_back(new pawn(blacks[i]->color, blacks[i]->typ, backup_table, blacks[i]->x, blacks[i]->y));
        else if (blacks[i]->color == 'B' && blacks[i]->typ == 'K')
            backup_blacks.push_back(new king(blacks[i]->color, blacks[i]->typ, backup_table, blacks[i]->x, blacks[i]->y));
        else if (blacks[i]->color == 'B' && blacks[i]->typ == 'Q')
            backup_blacks.push_back(new queen(blacks[i]->color, blacks[i]->typ, backup_table, blacks[i]->x, blacks[i]->y));
        else if (blacks[i]->color == 'B' && blacks[i]->typ == 'B')
            backup_blacks.push_back(new bishop(blacks[i]->color, blacks[i]->typ, backup_table, blacks[i]->x, blacks[i]->y));
        else if (blacks[i]->color == 'B' && blacks[i]->typ == 'N')
            backup_blacks.push_back(new knight(blacks[i]->color, blacks[i]->typ, backup_table, blacks[i]->x, blacks[i]->y));
        else if (blacks[i]->color == 'B' && blacks[i]->typ == 'R')
            backup_blacks.push_back(new rook(blacks[i]->color, blacks[i]->typ, backup_table, blacks[i]->x, blacks[i]->y));

    }
    backup_whites.clear();
    for (int i = 0; i < whites.size(); i++) {
        if (whites[i]->color == 'W' && whites[i]->typ == 'P')
            backup_whites.push_back(new pawn(whites[i]->color, whites[i]->typ, backup_table, whites[i]->x, whites[i]->y));
        else if (whites[i]->color == 'W' && whites[i]->typ == 'K')
            backup_whites.push_back(new king(whites[i]->color, whites[i]->typ, backup_table, whites[i]->x, whites[i]->y));
        else if (whites[i]->color == 'W' && whites[i]->typ == 'Q')
            backup_whites.push_back(new queen(whites[i]->color, whites[i]->typ, backup_table, whites[i]->x, whites[i]->y));
        else if (whites[i]->color == 'W' && whites[i]->typ == 'B')
            backup_whites.push_back(new bishop(whites[i]->color, whites[i]->typ, backup_table, whites[i]->x, whites[i]->y));
        else if (whites[i]->color == 'W' && whites[i]->typ == 'N')
            backup_whites.push_back(new knight(whites[i]->color, whites[i]->typ, backup_table, whites[i]->x, whites[i]->y));
        else if (whites[i]->color == 'W' && whites[i]->typ == 'R')
            backup_whites.push_back(new rook(whites[i]->color, whites[i]->typ, backup_table, whites[i]->x, whites[i]->y));
    }

    backup_Ptable = new mohre * *[8];
    for (int i = 0; i < 8; i++) {
        backup_Ptable[i] = new mohre * [8];
        for (int j = 0; j < 8; j++) {
            backup_Ptable[i][j] = NULL;
        }
    }
    for (int i = 0; i < backup_whites.size(); i++) {
        backup_Ptable[backup_whites[i]->x][backup_whites[i]->y] = backup_whites[i];
    }
    for (int i = 0; i < backup_blacks.size(); i++) {
        backup_Ptable[backup_blacks[i]->x][backup_blacks[i]->y] = backup_blacks[i];
    }
    backup_turn = turn;
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
        bool resets = false;
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
                if (mush.getPosition(*window).x > 842 && mush.getPosition(*window).x < 942 && mush.getPosition(*window).y > 705 && mush.getPosition(*window).y < 745)
                    resets = true;
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
                    }
                }
                if (flag) {
                move(firstclickx, firstclicky, leftclickx, leftclicky);
                turn = (turn == 'W') ? 'B' : 'W';
               
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
            if (check)
            {
                sf::Text endtext;
                endtext.setFont(peaces.font);
                endtext.setCharacterSize(25);
                endtext.setPosition(800, 400);
                endtext.setString("check mate");
                window->draw(endtext);
            }
        }
        if (whiteking->imchecked()) {
            drawlighterred(whiteking->y , whiteking->x );
            bool check = true;
            for (int i = 0; i < whites.size(); i++) {
                if (whites[i]->p_moves().size() > 0)
                    check = false;
            }
            if (check)
            {
                sf::Text endtext;
                endtext.setFont(peaces.font);
                endtext.setCharacterSize(25);
                endtext.setPosition(800, 400);
                endtext.setString("check mate");
                window->draw(endtext);
            }
        }
        if (resets) {
            reset();
            firstclicks = false;
            continue;
        }
        sf::Text turntext;
        turntext.setFont(peaces.font);
        turntext.setCharacterSize(40);
        turntext.setPosition(800, 350);
        if(turn=='W')
            turntext.setString("White");
        else 
            turntext.setString("Black");
        sf::Text resetbot;
        resetbot.setFont(peaces.font2);
        resetbot.setCharacterSize(40);
        resetbot.setPosition(850, 700);
        resetbot.setString("Reset");
        //resetbot.setColor(sf::Color::Cyan);
        sf::RectangleShape resetedge;
        //resetedge.setOutlineColor(sf::Color(0,0,200));
        resetedge.setFillColor(sf::Color(0,0,200));
        resetedge.setPosition(842, 705);
        resetedge.setSize(sf::Vector2f(100, 40));
        window->draw(resetedge);
        window->draw(turntext);
        window->draw(resetbot);
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
void board::reset() {
    table = new char** [8];
    for (int i = 0; i < 8; i++) {
        table[i] = new char* [8];
        for (int j = 0; j < 8; j++) {
            table[i][j] = new char[2];
            for (int k = 0; k < 2; k++) {
                table[i][j][k] = backup_table[i][j][k];
            }
        }
    }

    blacks.clear();
    for (int i = 0; i < backup_blacks.size(); i++) {
        if (backup_blacks[i]->color == 'B' && backup_blacks[i]->typ == 'P')
            blacks.push_back(new pawn(backup_blacks[i]->color, backup_blacks[i]->typ, table, backup_blacks[i]->x, backup_blacks[i]->y));
        else if (backup_blacks[i]->color == 'B' && backup_blacks[i]->typ == 'K')
            blacks.push_back(new king(backup_blacks[i]->color, backup_blacks[i]->typ, table, backup_blacks[i]->x, backup_blacks[i]->y));
        else if (backup_blacks[i]->color == 'B' && backup_blacks[i]->typ == 'Q')
            blacks.push_back(new queen(backup_blacks[i]->color, backup_blacks[i]->typ, table, backup_blacks[i]->x, backup_blacks[i]->y));
        else if (backup_blacks[i]->color == 'B' && backup_blacks[i]->typ == 'B')
            blacks.push_back(new bishop(backup_blacks[i]->color, backup_blacks[i]->typ, table, backup_blacks[i]->x, backup_blacks[i]->y));
        else if (backup_blacks[i]->color == 'B' && backup_blacks[i]->typ == 'N')
            blacks.push_back(new knight(backup_blacks[i]->color, backup_blacks[i]->typ, table, backup_blacks[i]->x, backup_blacks[i]->y));
        else if (backup_blacks[i]->color == 'B' && backup_blacks[i]->typ == 'R')
            blacks.push_back(new rook(backup_blacks[i]->color, backup_blacks[i]->typ, table, backup_blacks[i]->x, backup_blacks[i]->y));

    }
    whites.clear();
    for (int i = 0; i < backup_whites.size(); i++) {
        if (backup_whites[i]->color == 'W' && backup_whites[i]->typ == 'P')
            whites.push_back(new pawn(backup_whites[i]->color, backup_whites[i]->typ, table, backup_whites[i]->x, backup_whites[i]->y));
        else if (backup_whites[i]->color == 'W' && backup_whites[i]->typ == 'K')
            whites.push_back(new king(backup_whites[i]->color, backup_whites[i]->typ, table, backup_whites[i]->x, backup_whites[i]->y));
        else if (backup_whites[i]->color == 'W' && backup_whites[i]->typ == 'Q')
            whites.push_back(new queen(backup_whites[i]->color, backup_whites[i]->typ, table, backup_whites[i]->x, backup_whites[i]->y));
        else if (backup_whites[i]->color == 'W' && backup_whites[i]->typ == 'B')
            whites.push_back(new bishop(backup_whites[i]->color, backup_whites[i]->typ, table, backup_whites[i]->x, backup_whites[i]->y));
        else if (backup_whites[i]->color == 'W' && backup_whites[i]->typ == 'N')
            whites.push_back(new knight(backup_whites[i]->color, backup_whites[i]->typ, table, backup_whites[i]->x, backup_whites[i]->y));
        else if (backup_whites[i]->color == 'W' && backup_whites[i]->typ == 'R')
            whites.push_back(new rook(backup_whites[i]->color, backup_whites[i]->typ, table, backup_whites[i]->x, backup_whites[i]->y));

    }

    Ptable = new mohre * *[8];
    for (int i = 0; i < 8; i++) {
        Ptable[i] = new mohre * [8];
        for (int j = 0; j < 8; j++) {
            Ptable[i][j] = NULL;
        }
    }
    for (int i = 0; i < whites.size(); i++) {
        Ptable[whites[i]->x][whites[i]->y] = whites[i];
    }
    for (int i = 0; i < blacks.size(); i++) {
        Ptable[blacks[i]->x][blacks[i]->y] = blacks[i];
    }
    turn = backup_turn;
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
    peaces =  Peaces(table);
    updatesprite();
}