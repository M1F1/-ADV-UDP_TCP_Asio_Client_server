#include <cstdio>
#include <iostream>
#include <limits>
#include "Input_Output_Interface.h"
class Input_Output_con: public Input_Output_Interface{
    public:
        int get_move(){
              while(true){
                  int move = -1;
                  // reading int value, avoiding next input until new line
                  // character
                  if (!(std::cin >> move)) {
                     std::cout << "invalid character was added (ignoring the line)\n";
                     std::cin.clear();
                     std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                     return -1;
                    }
                  else if ((move < 0 || move > 8)) return -1;
                  else return move;
                  }
        }
    void show_welcome(){
        printf("\n----x------O-----X----o------\n\n\
    Welcome to Cross&Circle\n\n\
----O------X-----o----x------\n\n");
    }

    void show_board(char* board){
        printf("\t%c | %c | %c\n"
               "\t--+---+--\n"
               "\t%c | %c | %c\n"
               "\t--+---+--\n"
               "\t%c | %c | %c\n\n\n",
               board[0], board[1],
               board[2], board[3],
               board[4], board[5],
               board[6], board[7],
               board[8]
               );
    }
    void show_player_turn(char player){printf("Now moves (0-8): %c\n\n", player);}

    void show_move_error(char player){printf("Wrong move player: %c! Repeat plz!\n", player);}

    void show_draw(){printf("Draw!\n");}

    void show_winner(char player){
        if (player == 'x') printf("You win! Congratulations!\n");
        else printf("You loose! Player %c win the match!", player);
    } 
    ~Input_Output_con(){}
};
