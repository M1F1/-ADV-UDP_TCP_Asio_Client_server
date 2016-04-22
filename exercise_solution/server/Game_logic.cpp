#include "Game_logic.h"
Game_Logic::Game_Logic(){
            _board = new Board();
            _turn = _board->PLAYER1;
            _end = false;
            _winner = ' ';
            _players[0] = _board->PLAYER1;
            _players[1] = _board->PLAYER2;
}
Game_Logic::~Game_Logic(){ delete _board;}
bool Game_Logic::get_end()const{
    return _end;
}
char Game_Logic::get_winner()const{
    return _winner;
}
char Game_Logic::get_turn()const{
    return _turn;
}
char Game_Logic::get_turn_no()const{
    if (_turn == _players[0])
        return 0;
    else return 1;
}
char* Game_Logic::get_board()const{
    return _board->get_board();
}
bool Game_Logic::make_move( int where){
    if (_end) return true;
    if (!_board->put_on_board(where, _turn)) return false;
    if  (game_result()){
        _winner = _turn;
       _end = true;
       return true; 
    }
    if (!_board->move_available()){
       _end = true;
       return true;
    }
    if (_turn == _board->PLAYER1) _turn = _board->PLAYER2;
    else _turn = _board->PLAYER1;
    
    return true;
    
}
bool Game_Logic::game_result()const{
    char* b = _board->get_board();
    int w_p[][3] ={ // wining_pos
            { 0, 1, 2 },
            { 3, 4, 5 },
            { 6, 7, 8 },
            { 0, 3, 6 },
            { 1, 4, 7 },
            { 2, 5, 8 },
            { 0, 4, 8 },
            { 2, 4, 6 }
    };
    for (int i = 0; i < 8; i++){
        if (b[w_p[i][0]] == b[w_p[i][1]] &&
            b[w_p[i][1]] == b[w_p[i][2]] &&
            b[w_p[i][0]] != ' ')
            return true;
    }
    return false;
}
