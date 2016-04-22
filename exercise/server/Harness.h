#pragma once
#include "Game_logic.h"
#include "Board.h"
#include "Input_Output_con.h"
#include "InputOutputTCP.h"
#include "Input_Output_Proxy.h"
void ClearScreen(){
    for (int n = 0; n < 10; n++)
      printf( "\n\n\n\n\n\n\n\n\n\n" );
}
class Harness{
    Game_Logic* _game;
    Input_Output_Interface** _inputs;
    Input_Output_Proxy* _outputs;

    public:

    Harness(Input_Output_Proxy* outputs, Input_Output_Interface** inputs){
         _game = new Game_Logic();
         _inputs = inputs;
         _outputs = outputs; 
    }
    ~Harness(){delete _game;}
    void Start(){
        _outputs->show_welcome();
        int player_id;
        char player;
       while (true){ // game loop
            _outputs->show_board(_game->get_board()) ;
             player_id = _game->get_turn_no();
             player = _game->get_turn();
            _outputs->show_player_turn(player);
           while (true){
               // checking if 
                int move = _inputs[player_id]->get_move();
                if (move < 0){
                    _outputs->show_move_error(player);
                   continue; 
                } 
                if (_game->make_move(move) == false){
                    _outputs->show_move_error(player);
                   continue; 
                }
                ClearScreen();
                break;
            }
            if (!_game->get_end()) continue;

                _outputs->show_board(_game->get_board());
                char w = _game->get_winner();
                if (w == ' ') _outputs->show_draw();
                else _outputs->show_winner(w); 

                break;
       }
    }
};
