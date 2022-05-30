#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
using namespace std;
int* xy(char , char );
char* xy(int , int );
class mohre {
public:
    int x, y;
    char*** table;
    char color;
    char typ;
    mohre(char, char, char***, int, int);
    bool imchecked();
    char* lastmove(std::vector<char>& );
    virtual std::vector<char> p_moves();
    void undomove(char* a);
    void domove(char* a);
    virtual bool iamchecking();
};


class pawn :public mohre
{
public:
    pawn(char , char , char*** , int , int);
    std::vector<char> p_moves() override;
    bool iamchecking() override;
};
class king :public mohre
{
public:
    king(char, char, char***, int, int);
    std::vector<char> p_moves() override;
    bool iamchecking() override;
};
class queen :public mohre
{
public:
    queen(char, char, char***, int, int);
    std::vector<char> p_moves() override;
    bool iamchecking() override;
};
class bishop :public mohre
{
public:
    bishop(char, char, char***, int, int);
    std::vector<char> p_moves() override;
    bool iamchecking() override;
};
class knight :public mohre
{
public:
    knight(char, char, char***, int, int);
    std::vector<char> p_moves() override;
    bool iamchecking() override;
};
class rook :public mohre
{
public:
    rook(char, char, char***, int, int);
    std::vector<char> p_moves() override;
    bool iamchecking() override;
};
extern vector <mohre*> blacks;
extern vector <mohre*> whites;