#pragma once
#include <cstdio>
class Board{
    private:
        char* _board;
       
    public:
        char X = 'x';
        char O = 'o';
        int SIZE = 9;
        char PLAYER1 = X;
        char PLAYER2 = O;
        Board();
        char* get_board() const;
        bool put_on_board(int where, char sign);
        bool move_available(void)const;
        ~Board();
};
