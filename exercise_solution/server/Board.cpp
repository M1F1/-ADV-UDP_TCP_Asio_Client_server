#include "Board.h"
Board::Board(){
    _board = new char[9];
    for (int i = 0; i < SIZE; i++)
        _board[i] = ' ';
}
char* Board::get_board()const{
    return _board;
}
bool Board::put_on_board(int where, char sign){
    if (sign != X && sign != O){
        puts("Wrong sign!");
        return false;
    }
    if (where < 0 || where > 8){
        puts("Wrong cordinate!");
        return false;
    }
    if (_board[where] != ' '){
        return false;
    }
    _board[where] = sign;
    return true;
}
bool Board::move_available()const{
    for (int i = 0; i < SIZE; i++){
        if(_board[i] == ' ')
           return true;
    }
    return false;
}
Board::~Board(){
    delete[] _board;
}

