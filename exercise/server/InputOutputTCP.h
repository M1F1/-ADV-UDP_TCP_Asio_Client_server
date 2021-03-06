#pragma once
#include <ctime>
#include <iostream>
#include <string>
#include <cstdlib>
#include "boost/asio.hpp"
#include "boost/array.hpp"
#include "Input_Output_Interface.h"
using boost::asio::ip::tcp;
class InputOutputTCP: public Input_Output_Interface
{
private:
    tcp::acceptor acceptor_;
    tcp::socket socket_;
    boost::system::error_code ignored_error_;
    boost::array<char, 10> buf_;

public:
   InputOutputTCP(boost::asio::io_service& io_service, int bind_port)
       : acceptor_(/************************//* binding port with localhost*/)),
         socket_(/*******/)
   {
       try{
       std::cout << "Waiting for connection on port: " << bind_port << std::endl;
       
       /***********************/
       
       std::cout << "Player 2 connected!" << std::endl;
       }
       catch (std::exception& e)
       {
           std::cerr << e.what() << std::endl;
       }
   }
   
       int get_move()
       {
       // nalezy wyslac naglowek a nastepnie odebrac odpowiedz
           buf_[0] = /**/;
           /**********************************/
           /***********************/
           return (int) buf_[1];
       }
       
       
       /** w kazdej kolejnej metodzie nalezy zdefiniowac byte 0 naglowka datagramu oraz go wyslac */
       
       
       void show_welcome()
       {
           buf_[0] = /**/;
           /*******************************************/
       }

       void show_board(char* board)
       {
           buf_[0] = /**/; 
           for (int i = 0; i < 9; i++)
               buf_[i + 1] = board[i];
           /*******************************************/
       }

       void show_player_turn(char player)
       {
           buf_[0] = /**/;
           buf_[1] = player;
           /*******************************************/
           
       }
       void show_move_error(char player)
       {
           buf_[0] = /**/;
           buf_[1] = player;
           /*******************************************/
       }

       void show_draw(void)
       {
           buf_[0] = /**/;
           /*******************************************/
       }
       void show_winner(char player)
       {
           buf_[0] = /**/;
           buf_[1] = player;
           /*******************************************/
       }
};
