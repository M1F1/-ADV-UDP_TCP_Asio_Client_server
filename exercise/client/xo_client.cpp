#include <iostream>
#include "boost/array.hpp"
#include "boost/asio.hpp"
#include <string>

using boost::asio::ip::tcp;
class Cross_and_circle{
    private:
        boost::system::error_code error_;
        tcp::socket socket_;
        tcp::resolver resolver_;
        tcp::resolver::query query_;
        std::string message_;

        void ClearScreen(){
            for (int n = 0; n < 10; n++)
            printf( "\n\n\n\n\n\n\n\n\n\n" );
}

        void HandleShowWelcome()
        {
            std::cout<< "\n\tWelcome!\n\n"; 
        }
        void HandleShowBoard(char* board)
        {
        printf("\t%c | %c | %c\n"
               "\t==+===+==\n"
               "\t%c | %c | %c\n"
               "\t==+===+==\n"
               "\t%c | %c | %c\n\n\n",
               board[0], board[1],
               board[2], board[3],
               board[4], board[5],
               board[6], board[7],
               board[8]
              );

        }
        void HandleShowPlayerTurn(char player)
        {
            std::cout << "player " << player << " turn\n\n";  
        }
        void HandleShowMoveError(char player)
        {
            std::cout << "error , wrong move player\n " << player << std::endl; 
        }
        void HandleShowWinner(char player)
        {
            if (player == 'o') std::cout << "You win! congratz!\n";
            else std::cout << " You loose player! " << player << " win!\n"; 
        }
        void HandleShowDraw(void)
        {
            std::cout << "Draw!\n"; 
        }
        int HandleGetMoveRequest()
        {

            std::cout << "Your move (0-8)!\n";
            int i;
            scanf("%i", &i);
            ClearScreen();
            return i;
        }
    public:
        Cross_and_circle(boost::asio::io_service &io_service, char* host, char* port)
            : socket_(/*****/), resolver_(/*****/), query_(/*****/), message_("")
        {
            try{
           tcp::resolver::iterator endpoint_iterator = resolver_.resolve(/****/);
           boost::asio::connect(/*********/);
           std::cout << "Connected to: " << host << " " << port << std::endl;
            }
           catch (std::exception& e)
           {
           std::cerr << e.what() << std::endl;
           }


        }
        bool HandleSingleRequest()
        {
            boost::array<char, 10> buf;
            size_t len = boost::asio::read(socket_, boost::asio::buffer(buf,10));
            if (error_ == boost::asio::error::eof)
                  return false;
              else if (error_)
                  throw boost::system::system_error(error_); 
            if (len == 0)
            {
               std::cout << "Disconnected!\n";
               return false; 
            }
            switch(buf[0])
            {
                case /**/:
                    {
                    int move = HandleGetMoveRequest();
                    boost::array<char, 10> buf_;
                    buf_[0] = /**/;
                    buf_[1] = (char) move;
                    boost::asio::write(socket_, boost::asio::buffer(buf_), error_);
                 
                    }
                    break;

                case /**/: // show welcome
                    {
                    HandleShowWelcome();
                    }
                    break;
           
                case /**/: // show draw
                    HandleShowDraw();
                    break;
                case /**/:
                    {
                    char board[9];
                    for (int i = 1; i < 10; i++)
                        board[i - 1] = buf[i];
                   HandleShowBoard(board);
                   }
                   break;
                case /**/: // show player_turn
                   {
                  HandleShowPlayerTurn(buf[1]);
                   }
                  break;
                case /**/: // show move error
                  {
                    HandleShowMoveError(buf[1]);
                  }
                  break;
                case /**/: // show winner
                  {
                   HandleShowWinner(buf[1]);
                  }
                  break;
                default:
                  std::cout << "Invalid packet ID\n";
                  return false;
            }
            return true;
        }
};
int main(int argc, char* argv[])
{

    try
       {

           if (argc != 3)
           {
               std::cerr << "Usage: client <host>" << std::endl;
               return 1; 
           }
           boost::asio::io_service io_service;
           Cross_and_circle* xo = new Cross_and_circle(io_service, argv[1], argv[2]);
           for(;;)
           {
               if (!xo->HandleSingleRequest()) break;
           }
       }
    catch(...){}
}
