#include <vector>
#include "mohre.h"
using namespace std;
vector <mohre*> blacks;
vector <mohre*> whites;

char* xy(int x, int y) {
    char* a = new char[2];
    a[0] = 'a' + y;
    a[1] = '8' - x;
    return a;
}
int* xy(char x, char y) {
    int* a = new int[2];
    a[0] = '8' - y;
    a[1] = x - 'a';
    return a;
}
mohre::mohre(char color, char typ, char*** t, int x, int y)
{
    this->table = t;
    this->x = x;
    this->y = y;
    this->color = color;
    this->typ = typ;
}
bool mohre:: imchecked() {
    if (color == 'B') {
        for (int i = 0; i < whites.size(); i++) {
            if (whites[i]->iamchecking()) {
                //cout << whites[i]->typ << " " << whites[i]->color << "checker" << x << " " << y << endl;
                return true;
            }
        }
        return false;
    }
    if (color == 'W') {
        for (int i = 0; i < blacks.size(); i++) {
            if (blacks[i]->iamchecking())
                return true;
        }
        return false;
    }
}
char* mohre::lastmove( vector<char>& a) {
    char* ans = new char[8];
    for (int i = 0; i < 8; i++)
        ans[i] = a[a.size() - 8 + i];
    return ans;
}
vector<char> mohre ::p_moves()
{
    vector<char> a;
    return a;
}
void mohre::undomove(char* a) {
    int* fInt = xy(a[0], a[1]);
    int* cInt = xy(a[4], a[5]);
    table[fInt[0]][fInt[1]][0] = a[2];
    table[fInt[0]][fInt[1]][1] = a[3];
    table[cInt[0]][cInt[1]][0] = a[6];
    table[cInt[0]][cInt[1]][1] = a[7];
    x = fInt[0];
    y = fInt[1];
    delete fInt;
    delete cInt;
}
void mohre::domove(char* a) {
    int* fInt = xy(a[0], a[1]);
    int* cInt = xy(a[4], a[5]);
    table[fInt[0]][fInt[1]][0] = '-';
    table[fInt[0]][fInt[1]][1] = '-';
    table[cInt[0]][cInt[1]][0] = a[2];
    table[cInt[0]][cInt[1]][1] = a[3];
    x = cInt[0];
    y = cInt[1];
    delete fInt;
    delete cInt;
}
bool mohre::iamchecking() {
    return false;
}

pawn::pawn(char color, char typ, char*** t, int x, int y)
    :mohre(color, typ, t, x, y)
{
}
vector<char> pawn::p_moves()
{
    vector<char> ans;
    if (!(table[x][y][0] == typ && table[x][y][1] == color))
        return ans;
    int tx = x, ty = y;
    int xm = (table[x][y][1] == 'B') ? 1 : -1;
    //first move 
    if (0 <= x + xm && x + xm < 8)
        if (table[x + xm][y][0] == '-') {
            x = x + xm;
            char dest[] = { table[x][y][0] ,table[x][y][1] };
            table[x][y][0] = table[tx][y][0];
            table[x][y][1] = table[tx][y][1];
            table[tx][ty][0] = '-';
            table[tx][ty][1] = '-';
            if (!imchecked()) {
                char* fChar = xy(tx, ty);
                char* cChar = xy(x, y);
                ans.push_back(fChar[0]);
                ans.push_back(fChar[1]);
                ans.push_back(table[x][y][0]);
                ans.push_back(table[x][y][1]);
                ans.push_back(cChar[0]);
                ans.push_back(cChar[1]);
                ans.push_back(dest[0]);
                ans.push_back(dest[1]);
                delete fChar;
                delete cChar;
                char* tChar = lastmove(ans);
                undomove(tChar);
                delete tChar;
            }
            else {
                vector <char> tans;
                char* fChar = xy(tx, ty);
                char* cChar = xy(x, y);
                tans.push_back(fChar[0]);
                tans.push_back(fChar[1]);
                tans.push_back(table[x][y][0]);
                tans.push_back(table[x][y][1]);
                tans.push_back(cChar[0]);
                tans.push_back(cChar[1]);
                tans.push_back(dest[0]);
                tans.push_back(dest[1]);
                delete fChar;
                delete cChar;
                char* tChar = lastmove(tans);
                undomove(tChar);
                delete tChar;
            }
        }

    //second move
    if ((0 <= x + xm && x + xm < 8) && (0 <= y + 1 && y + 1 < 8))
        if (table[x + xm][y + 1][0] != '-' && table[x + xm][y + 1][1] != color && table[x + xm][y + 1][0] != 'K') {
            x = x + xm;
            y = y + 1;
            char dest[] = { table[x][y][0] ,table[x][y][1] };
            table[x][y][0] = table[tx][ty][0];
            table[x][y][1] = table[tx][ty][1];
            table[tx][ty][0] = '-';
            table[tx][ty][1] = '-';
            if (!imchecked()) {
                char* fChar = xy(tx, ty);
                char* cChar = xy(x, y);
                ans.push_back(fChar[0]);
                ans.push_back(fChar[1]);
                ans.push_back(table[x][y][0]);
                ans.push_back(table[x][y][1]);
                ans.push_back(cChar[0]);
                ans.push_back(cChar[1]);
                ans.push_back(dest[0]);
                ans.push_back(dest[1]);
                delete fChar;
                delete cChar;
                char* tChar = lastmove(ans);
                undomove(tChar);
                delete tChar;
            }
            else {
                vector <char> tans;
                char* fChar = xy(tx, ty);
                char* cChar = xy(x, y);
                tans.push_back(fChar[0]);
                tans.push_back(fChar[1]);
                tans.push_back(table[x][y][0]);
                tans.push_back(table[x][y][1]);
                tans.push_back(cChar[0]);
                tans.push_back(cChar[1]);
                tans.push_back(dest[0]);
                tans.push_back(dest[1]);
                delete fChar;
                delete cChar;
                char* tChar = lastmove(tans);
                undomove(tChar);
                delete tChar;
            }
        }
    //third move
    if ((0 <= x + xm && x + xm < 8) && (0 <= y - 1 && y - 1 < 8))
        if (table[x + xm][y - 1][0] != '-' && table[x + xm][y - 1][1] != color && table[x + xm][y - 1][0] != 'K') {
            x = x + xm;
            y = y - 1;
            char dest[] = { table[x][y][0] ,table[x][y][1] };
            table[x][y][0] = table[tx][ty][0];
            table[x][y][1] = table[tx][ty][1];
            table[tx][ty][0] = '-';
            table[tx][ty][1] = '-';
            if (!imchecked()) {
                char* fChar = xy(tx, ty);
                char* cChar = xy(x, y);
                ans.push_back(fChar[0]);
                ans.push_back(fChar[1]);
                ans.push_back(table[x][y][0]);
                ans.push_back(table[x][y][1]);
                ans.push_back(cChar[0]);
                ans.push_back(cChar[1]);
                ans.push_back(dest[0]);
                ans.push_back(dest[1]);
                delete fChar;
                delete cChar;
                char* tChar = lastmove(ans);
                undomove(tChar);
                delete tChar;
            }
            else {
                vector <char> tans;
                char* fChar = xy(tx, ty);
                char* cChar = xy(x, y);
                tans.push_back(fChar[0]);
                tans.push_back(fChar[1]);
                tans.push_back(table[x][y][0]);
                tans.push_back(table[x][y][1]);
                tans.push_back(cChar[0]);
                tans.push_back(cChar[1]);
                tans.push_back(dest[0]);
                tans.push_back(dest[1]);
                delete fChar;
                delete cChar;
                char* tChar = lastmove(tans);
                undomove(tChar);
                delete tChar;
            }
        }
    //forth move
    if ((table[x][y][1] == 'B' && x == 1) || (table[x][y][1] == 'W' && x == 6))
        if (table[x + xm][y][0] == '-' && table[x + 2 * xm][y][1] == '-') {
            x = x + 2 * xm;
            char dest[] = { table[x][y][0] ,table[x][y][1] };
            table[x][y][0] = table[tx][ty][0];
            table[x][y][1] = table[tx][ty][1];
            table[tx][ty][0] = '-';
            table[tx][ty][1] = '-';
            if (!imchecked()) {
                char* fChar = xy(tx, ty);
                char* cChar = xy(x, y);
                ans.push_back(fChar[0]);
                ans.push_back(fChar[1]);
                ans.push_back(table[x][y][0]);
                ans.push_back(table[x][y][1]);
                ans.push_back(cChar[0]);
                ans.push_back(cChar[1]);
                ans.push_back(dest[0]);
                ans.push_back(dest[1]);
                delete fChar;
                delete cChar;
                char* tChar = lastmove(ans);
                undomove(tChar);
                delete tChar;
            }
            else {
                vector <char> tans;
                char* fChar = xy(tx, ty);
                char* cChar = xy(x, y);
                tans.push_back(fChar[0]);
                tans.push_back(fChar[1]);
                tans.push_back(table[x][y][0]);
                tans.push_back(table[x][y][1]);
                tans.push_back(cChar[0]);
                tans.push_back(cChar[1]);
                tans.push_back(dest[0]);
                tans.push_back(dest[1]);
                delete fChar;
                delete cChar;
                char* tChar = lastmove(tans);
                undomove(tChar);
                delete tChar;
            }
        }
    return ans;
}
bool pawn::iamchecking()
{
    if (!(table[x][y][0] == typ && table[x][y][1] == color))
        return false;
    int xm = (table[x][y][1] == 'B') ? 1 : -1;
    if ((0 <= x + xm && x + xm < 8) && (0 <= y + 1 && y + 1 < 8))
        if (table[x + xm][y + 1][0] == 'K' && table[x + xm][y + 1][1] != table[x][y][1])
        {
            //cout << "pawn" << endl;
            return true;
        }
    if ((0 <= x + xm && x + xm < 8) && (0 <= y - 1 && y - 1 < 8))
        if (table[x + xm][y - 1][0] == 'K' && table[x + xm][y - 1][1] != table[x][y][1])
        {
            //cout << "pawn" << endl;
            return true;
        }
    return false;
}

king::king(char color, char typ, char*** t, int x, int y)
    :mohre(color, typ, t, x, y)
{
}
vector<char> king::p_moves()
{
    int xym[8][2] = { {-1,-1},{-1,0},{-1,1},{0,-1},{0,1},{1,-1},{1,0},{1,1} };
    //cout << "in pmoves king!!!!!!" << endl;
    //cout << typ << " " << color << endl;
    vector<char> ans;
    if (!(table[x][y][0] == typ && table[x][y][1] == color)) {
        //cout << "king has been stabbed monkas";
        return ans;
    }
    int tx = x, ty = y;
    for (int i = 0; i < 8; i++) {
        if ((0 <= x + xym[i][0] && x + xym[i][0] < 8) && (0 <= y + xym[i][1] && y + xym[i][1] < 8)) {
            if (table[x + xym[i][0]][y + xym[i][1]][1] != table[x][y][1] && table[x + xym[i][0]][y + xym[i][1]][0] != 'K')
            {
                x = x + xym[i][0];
                y = y + xym[i][1];
                char dest[] = { table[x][y][0] ,table[x][y][1] };
                table[x][y][0] = table[tx][ty][0];
                table[x][y][1] = table[tx][ty][1];
                table[tx][ty][0] = '-';
                table[tx][ty][1] = '-';
                if (!imchecked()) {
                    char* fChar = xy(tx, ty);
                    char* cChar = xy(x, y);
                    ans.push_back(fChar[0]);
                    ans.push_back(fChar[1]);
                    ans.push_back(table[x][y][0]);
                    ans.push_back(table[x][y][1]);
                    ans.push_back(cChar[0]);
                    ans.push_back(cChar[1]);
                    ans.push_back(dest[0]);
                    ans.push_back(dest[1]);
                    delete fChar;
                    delete cChar;
                    char* tChar = lastmove(ans);
                    undomove(tChar);
                    delete tChar;
                }
                else {
                    vector <char> tans;
                    char* fChar = xy(tx, ty);
                    char* cChar = xy(x, y);
                    tans.push_back(fChar[0]);
                    tans.push_back(fChar[1]);
                    tans.push_back(table[x][y][0]);
                    tans.push_back(table[x][y][1]);
                    tans.push_back(cChar[0]);
                    tans.push_back(cChar[1]);
                    tans.push_back(dest[0]);
                    tans.push_back(dest[1]);
                    delete fChar;
                    delete cChar;
                    char* tChar = lastmove(tans);
                    undomove(tChar);
                    delete tChar;
                }
            }
        }
    }
    return ans;

}
bool king::iamchecking() 
{
    if (!(table[x][y][0] == typ && table[x][y][1] == color)) {
        return false;
    }
    int xym[8][2] = { {-1,-1},{-1,0},{-1,1},{0,-1},{0,1},{1,-1},{1,0},{1,1} };
    for (int i = 0; i < 8; i++)
    {
        if ((0 <= x + xym[i][0] && x + xym[i][0] < 8) && (0 <= y + xym[i][1] && y + xym[i][1] < 8)) {
            if (table[x + xym[i][0]][y + xym[i][1]][1] != table[x][y][1] && table[x + xym[i][0]][y + xym[i][1]][0] == 'K') {
                {
                    //cout << "king" << endl;
                    return true;
                }
            }
        }
    }
    return false;
}

queen::queen(char color, char typ, char*** t, int x, int y)
    :mohre(color, typ, t, x, y)
{
}
vector<char> queen::p_moves()
{
    int xym[8][2] = { {-1,0},{1,0},{0,1},{0,-1},{-1,-1},{1,-1},{1,1},{-1,1} };
    //cout << "in pmoves queebn!!!!!!" << endl;
    //cout << typ << " " << color << endl;
    vector<char> ans;
    if (!(table[x][y][0] == typ && table[x][y][1] == color)) {
        //cout << "queen has fallen to the enemys";
        return ans;
    }
    int tx = x, ty = y;
    int i = 0;
    while (i < 8)
    {
        int j = 1;
        bool flag = true;
        while (flag)
        {
            if ((!((0 <= x + xym[i][0] * j && x + xym[i][0] * j < 8) && (0 <= y + xym[i][1] * j && y + xym[i][1] * j < 8))) || (table[x + xym[i][0] * j][y + xym[i][1] * j][0] == 'K')) {
                flag = false;
                continue;
            }
            if (!((table[x + xym[i][0] * j][y + xym[i][1] * j][1] == '-'))) {
                flag = false;
            }
            if (table[x + xym[i][0] * j][y + xym[i][1] * j][1] != color) {
                x = x + xym[i][0] * j;
                y = y + xym[i][1] * j;
                char dest[] = { table[x][y][0] ,table[x][y][1] };
                table[x][y][0] = table[tx][ty][0];
                table[x][y][1] = table[tx][ty][1];
                table[tx][ty][0] = '-';
                table[tx][ty][1] = '-';
                if (!imchecked()) {
                    char* fChar = xy(tx, ty);
                    char* cChar = xy(x, y);
                    ans.push_back(fChar[0]);
                    ans.push_back(fChar[1]);
                    ans.push_back(table[x][y][0]);
                    ans.push_back(table[x][y][1]);
                    ans.push_back(cChar[0]);
                    ans.push_back(cChar[1]);
                    ans.push_back(dest[0]);
                    ans.push_back(dest[1]);
                    delete fChar;
                    delete cChar;
                    char* tChar = lastmove(ans);
                    undomove(tChar);
                    delete tChar;
                }
                else {
                    vector <char> tans;
                    char* fChar = xy(tx, ty);
                    char* cChar = xy(x, y);
                    tans.push_back(fChar[0]);
                    tans.push_back(fChar[1]);
                    tans.push_back(table[x][y][0]);
                    tans.push_back(table[x][y][1]);
                    tans.push_back(cChar[0]);
                    tans.push_back(cChar[1]);
                    tans.push_back(dest[0]);
                    tans.push_back(dest[1]);
                    delete fChar;
                    delete cChar;
                    char* tChar = lastmove(tans);
                    undomove(tChar);
                    delete tChar;
                }
            }
            j++;
        }
        i++;
    }
    return ans;
}
bool queen::iamchecking()
{
    if (!(table[x][y][0] == typ && table[x][y][1] == color)) {
        return false;
    }
    int xym[8][2] = { {-1,0},{1,0},{0,1},{0,-1},{-1,-1},{1,-1},{1,1},{-1,1} };
    int i = 0;
    while (i < 8) {
        int j = 1;

        while ((((0 <= x + xym[i][0] * j && x + xym[i][0] * j < 8) && (0 <= y + xym[i][1] * j && y + xym[i][1] * j < 8)))) {
            if (table[x + xym[i][0] * j][y + xym[i][1] * j][1] != color && table[x + xym[i][0] * j][y + xym[i][1] * j][0] == 'K')
            {
                //cout << "mbooba" << endl;
                return true;
            }
            if (table[x + xym[i][0] * j][y + xym[i][1] * j][1] != '-')
                break;
            j++;
        }
        i++;
    }
    return false;
}

bishop::bishop(char color, char typ, char*** t, int x, int y)
    :mohre(color, typ, t, x, y)
{
}
vector<char> bishop::p_moves() 
{
    int xym[4][2] = { {-1,-1},{1,-1},{1,1},{-1,1} };
    //cout << "in pmoves bishop!!!!!!" << endl;
    //cout << typ << " " << color << endl;
    vector<char> ans;
    if (!(table[x][y][0] == typ && table[x][y][1] == color)) {
        //cout << "bishop has fallen to the enemys";
        return ans;
    }
    int tx = x, ty = y;
    int i = 0;
    while (i < 4)
    {
        int j = 1;
        bool flag = true;
        while (flag)
        {
            if ((!((0 <= x + xym[i][0] * j && x + xym[i][0] * j < 8) && (0 <= y + xym[i][1] * j && y + xym[i][1] * j < 8))) || (table[x + xym[i][0] * j][y + xym[i][1] * j][0] == 'K')) {
                flag = false;
                continue;
            }
            if (!(table[x + xym[i][0] * j][y + xym[i][1] * j][1] == '-')) {
                flag = false;
            }
            if (table[x + xym[i][0] * j][y + xym[i][1] * j][1] != color) {
                x = x + xym[i][0] * j;
                y = y + xym[i][1] * j;
                char dest[] = { table[x][y][0] ,table[x][y][1] };
                table[x][y][0] = table[tx][ty][0];
                table[x][y][1] = table[tx][ty][1];
                table[tx][ty][0] = '-';
                table[tx][ty][1] = '-';
                if (!imchecked()) {
                    char* fChar = xy(tx, ty);
                    char* cChar = xy(x, y);
                    ans.push_back(fChar[0]);
                    ans.push_back(fChar[1]);
                    ans.push_back(table[x][y][0]);
                    ans.push_back(table[x][y][1]);
                    ans.push_back(cChar[0]);
                    ans.push_back(cChar[1]);
                    ans.push_back(dest[0]);
                    ans.push_back(dest[1]);
                    delete fChar;
                    delete cChar;
                    char* tChar = lastmove(ans);
                    undomove(tChar);
                    delete tChar;
                }
                else {
                    vector <char> tans;
                    char* fChar = xy(tx, ty);
                    char* cChar = xy(x, y);
                    tans.push_back(fChar[0]);
                    tans.push_back(fChar[1]);
                    tans.push_back(table[x][y][0]);
                    tans.push_back(table[x][y][1]);
                    tans.push_back(cChar[0]);
                    tans.push_back(cChar[1]);
                    tans.push_back(dest[0]);
                    tans.push_back(dest[1]);
                    delete fChar;
                    delete cChar;
                    char* tChar = lastmove(tans);
                    undomove(tChar);
                    delete tChar;
                }
            }
            j++;
        }
        i++;
    }

    return ans;
}
bool bishop::iamchecking() 
{
    if (!(table[x][y][0] == typ && table[x][y][1] == color)) {
        return false;
    }
    int xym[4][2] = { {-1,-1},{1,-1},{1,1},{-1,1} };
    int i = 0;
    while (i < 4) {
        int j = 1;

        while ((((0 <= x + xym[i][0] * j && x + xym[i][0] * j < 8) && (0 <= y + xym[i][1] * j && y + xym[i][1] * j < 8)))) {
            if (table[x + xym[i][0] * j][y + xym[i][1] * j][1] != color && table[x + xym[i][0] * j][y + xym[i][1] * j][0] == 'K')
            {
                //cout << x + xym[i][0] * j << " " << y + xym[i][1] * j << "checked"<<endl;
                return true;
            }
            if (table[x + xym[i][0] * j][y + xym[i][1] * j][1] != '-')
                break;
            j++;
        }
        i++;
    }
    return false;
}

knight::knight(char color, char typ, char*** t, int x, int y)
    :mohre(color, typ, t, x, y)
{
}
vector<char> knight::p_moves() 
{
    int xym[8][2] = { {-1,-2},{-2,-1},{-2,1},{-1,2},{1,-2},{2,-1},{2,1},{1,2} };
    //cout << "in pmoves knight!!!!!!" << endl;
    //cout << typ << " " << color << endl;
    vector<char> ans;
    if (!(table[x][y][0] == typ && table[x][y][1] == color)) {
        //cout << "knight has been stabbed ";
        return ans;
    }
    int tx = x, ty = y;
    for (int i = 0; i < 8; i++) {
        if ((0 <= x + xym[i][0] && x + xym[i][0] < 8) && (0 <= y + xym[i][1] && y + xym[i][1] < 8)) {
            if (table[x + xym[i][0]][y + xym[i][1]][1] != table[x][y][1] && table[x + xym[i][0]][y + xym[i][1]][0] != 'K')
            {
                x = x + xym[i][0];
                y = y + xym[i][1];
                char dest[] = { table[x][y][0] ,table[x][y][1] };
                table[x][y][0] = table[tx][ty][0];
                table[x][y][1] = table[tx][ty][1];
                table[tx][ty][0] = '-';
                table[tx][ty][1] = '-';
                if (!imchecked()) {
                    char* fChar = xy(tx, ty);
                    char* cChar = xy(x, y);
                    ans.push_back(fChar[0]);
                    ans.push_back(fChar[1]);
                    ans.push_back(table[x][y][0]);
                    ans.push_back(table[x][y][1]);
                    ans.push_back(cChar[0]);
                    ans.push_back(cChar[1]);
                    ans.push_back(dest[0]);
                    ans.push_back(dest[1]);
                    delete fChar;
                    delete cChar;
                    char* tChar = lastmove(ans);
                    undomove(tChar);
                    delete tChar;
                }
                else {
                    vector <char> tans;
                    char* fChar = xy(tx, ty);
                    char* cChar = xy(x, y);
                    tans.push_back(fChar[0]);
                    tans.push_back(fChar[1]);
                    tans.push_back(table[x][y][0]);
                    tans.push_back(table[x][y][1]);
                    tans.push_back(cChar[0]);
                    tans.push_back(cChar[1]);
                    tans.push_back(dest[0]);
                    tans.push_back(dest[1]);
                    delete fChar;
                    delete cChar;
                    char* tChar = lastmove(tans);
                    undomove(tChar);
                    delete tChar;
                }
            }
        }
    }
    return ans;

}
bool knight::iamchecking()
{
    if (!(table[x][y][0] == typ && table[x][y][1] == color)) {
        return false;
    }
    int xym[8][2] = { {-1,-2},{-2,-1},{-2,1},{-1,2},{1,-2},{2,-1},{2,1},{1,2} };
    for (int i = 0; i < 8; i++)
    {
        if ((0 <= x + xym[i][0] && x + xym[i][0] < 8) && (0 <= y + xym[i][1] && y + xym[i][1] < 8)) {
            if (table[x + xym[i][0]][y + xym[i][1]][1] != table[x][y][1] && table[x + xym[i][0]][y + xym[i][1]][0] == 'K') {
                {
                    //cout << "mbooba" << endl;
                    return true;
                }
            }
        }
    }
    return false;
}

rook::rook(char color, char typ, char*** t, int x, int y)
    :mohre(color, typ, t, x, y)
{
}
vector<char> rook::p_moves()
{
    int xym[4][2] = { {-1,0},{1,0},{0,1},{0,-1} };
    //cout << "in pmoves rooook!!!!!!" << endl;
    //cout << typ << " " << color << endl;
    vector<char> ans;
    if (!(table[x][y][0] == typ && table[x][y][1] == color)) {
        //cout << "rook has fallen to the enemys";
        return ans;
    }
    int tx = x, ty = y;
    int i = 0;
    while (i < 4)
    {
        int j = 1;
        bool flag = true;
        while (flag)
        {
            if ((!((0 <= x + xym[i][0] * j && x + xym[i][0] * j < 8) && (0 <= y + xym[i][1] * j && y + xym[i][1] * j < 8))) || (table[x + xym[i][0] * j][y + xym[i][1] * j][0] == 'K')) {
                flag = false;
                continue;
            }
            if (!(table[x + xym[i][0] * j][y + xym[i][1] * j][1] == '-')) {
                flag = false;
            }
            if (table[x + xym[i][0] * j][y + xym[i][1] * j][1] != color) {
                x = x + xym[i][0] * j;
                y = y + xym[i][1] * j;
                char dest[] = { table[x][y][0] ,table[x][y][1] };
                table[x][y][0] = table[tx][ty][0];
                table[x][y][1] = table[tx][ty][1];
                table[tx][ty][0] = '-';
                table[tx][ty][1] = '-';
                if (!imchecked()) {
                    char* fChar = xy(tx, ty);
                    char* cChar = xy(x, y);
                    ans.push_back(fChar[0]);
                    ans.push_back(fChar[1]);
                    ans.push_back(table[x][y][0]);
                    ans.push_back(table[x][y][1]);
                    ans.push_back(cChar[0]);
                    ans.push_back(cChar[1]);
                    ans.push_back(dest[0]);
                    ans.push_back(dest[1]);
                    delete fChar;
                    delete cChar;
                    char* tChar = lastmove(ans);
                    undomove(tChar);
                    delete tChar;
                }
                else {
                    vector <char> tans;
                    char* fChar = xy(tx, ty);
                    char* cChar = xy(x, y);
                    tans.push_back(fChar[0]);
                    tans.push_back(fChar[1]);
                    tans.push_back(table[x][y][0]);
                    tans.push_back(table[x][y][1]);
                    tans.push_back(cChar[0]);
                    tans.push_back(cChar[1]);
                    tans.push_back(dest[0]);
                    tans.push_back(dest[1]);
                    delete fChar;
                    delete cChar;
                    char* tChar = lastmove(tans);
                    undomove(tChar);
                    delete tChar;
                }
            }
            j++;
        }
        i++;
    }
    return ans;
}
bool rook::iamchecking()
{
    if (!(table[x][y][0] == typ && table[x][y][1] == color)) {
        return false;
    }
    int xym[4][2] = { {-1,0},{1,0},{0,1},{0,-1} };
    int i = 0;
    while (i < 4) {
        int j = 1;

        while ((((0 <= x + xym[i][0] * j && x + xym[i][0] * j < 8) && (0 <= y + xym[i][1] * j && y + xym[i][1] * j < 8)))) {
            if (table[x + xym[i][0] * j][y + xym[i][1] * j][1] != color && table[x + xym[i][0] * j][y + xym[i][1] * j][0] == 'K')
            {
                // cout << "the rook" << endl;
                return true;
            }
            if (table[x + xym[i][0] * j][y + xym[i][1] * j][1] != '-')
                break;
            j++;
        }
        i++;
    }
    return false;
}