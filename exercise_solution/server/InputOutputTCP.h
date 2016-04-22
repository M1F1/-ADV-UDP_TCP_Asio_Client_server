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
       : acceptor_(io_service, tcp::endpoint(tcp::v4(), bind_port /* binding port with localhost*/)),
         socket_(io_service)
   {
       try{
       std::cout << "Waiting for connection on port: " << bind_port << std::endl;
       acceptor_.accept(socket_);
       std::cout << "Player 2 connected!" << std::endl;
       }
       catch (std::exception& e)
       {
           std::cerr << e.what() << std::endl;
       }
   }
       int get_move()
       {
           buf_[0] = 'G';
           boost::asio::write(socket_, boost::asio::buffer(buf_), ignored_error_);
           boost::asio::read(socket_, boost::asio::buffer(buf_,10));
           return (int) buf_[1];
       }
       void show_welcome()
       {
           buf_[0] = 'W';
           boost::asio::write(socket_, boost::asio::buffer(buf_), ignored_error_);
       }

       void show_board(char* board)
       {
           buf_[0] = 'B'; 
           for (int i = 0; i < 9; i++)
               buf_[i + 1] = board[i];
           boost::asio::write(socket_, boost::asio::buffer(buf_), ignored_error_);
       }

       void show_player_turn(char player)
       {
           buf_[0] = 'P';
           buf_[1] = player;
           boost::asio::write(socket_, boost::asio::buffer(buf_), ignored_error_);
       }
       void show_move_error(char player)
       {
           buf_[0] = 'E';
           buf_[1] = player;
           boost::asio::write(socket_, boost::asio::buffer(buf_), ignored_error_);
       }

       void show_draw(void)
       {
           buf_[0] = 'D';
           boost::asio::write(socket_, boost::asio::buffer(buf_), ignored_error_);
       }
       void show_winner(char player)
       {
           buf_[0] = 'I';
           buf_[1] = player;
           boost::asio::write(socket_, boost::asio::buffer(buf_), ignored_error_);
       }
};
