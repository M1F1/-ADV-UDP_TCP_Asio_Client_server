#pragma once
#include "Input_Output_Interface.h"
#include <vector>
class Input_Output_Proxy: public Input_Output_Interface
{
    private:
        std::vector<Input_Output_Interface*> outputs_;
    public:
       /* ~Output_Proxy()
        {
             for (auto output: outputs_)
                 delete output;
        }*/
        int get_move(){return 0;}
        void register_output(Input_Output_Interface* ptr)
        {
            outputs_.push_back(ptr);
        }
        void show_welcome()
        {
            for ( auto output: outputs_ )
                output->show_welcome();
        }
        void show_board(char* board)
        {
            for ( auto output: outputs_ )
                output->show_board(board);
        }
        void show_player_turn(char player)
        {
            for ( auto output: outputs_ )
                output->show_player_turn(player);
        }
        void show_move_error(char player)
        {
            for ( auto output: outputs_ )
                output->show_move_error(player);
        }
        void show_draw(void)
        {
            for ( auto output: outputs_ )
                output->show_draw();
        }
        void show_winner(char player)
        {
            for ( auto output: outputs_ )
                output->show_winner(player);
        }
};
