#pragma once
class Input_Output_Interface{
    public:

        virtual ~Input_Output_Interface(){}

        virtual int get_move() = 0;

        virtual void show_welcome()= 0;

        virtual void show_board(char* board)= 0;    

        virtual void show_player_turn(char player)= 0;

        virtual void show_move_error(char player)= 0;

        virtual void show_draw(void)= 0;

        virtual void show_winner(char player)= 0;
};
