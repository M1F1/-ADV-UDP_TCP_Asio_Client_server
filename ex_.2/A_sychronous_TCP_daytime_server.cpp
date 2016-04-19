// program implementujacy serwer z TCP
#include <ctime>
#include <iostream>
#include <string>
#include "boost/asio.hpp"

using boost::asio::ip::tcp;

// tworzymy funkcje make_daytime_string() ktora bedzie tworzyla string
// wysylany spowrotem do clienta. Funkcja ta bedzie powszechnie uzywana
//
std::string make_daytime_string()
{
    using namespace std; // for time_t, time and ctime
    time_t now = time(0);
    return ctime(&now);
}

int main()
{
    try
    {
        boost::asio::io_service io_service;
       // obiekt typu ip::tcp::aceptor zostanie stworzony aby nasluchiwac
       // nowych polaczen. jest inicjalizowany po przez tcp na porcie 13 dla
       // ipv4 
        tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), 1241));
        // to jest serwer iteracyjny, co oznacza ze ma otwarte jedno polaczenie
        // w ty m samym czasie. Tworzenie gniazda sieciowego ktore bedzie
        // reprezentowalo  polaczenie z klientem i czekalo na polaczenie.
        for(;;)
        {
            tcp::socket socket(io_service);
            std::cout << "Waiting for connection on port: 1241 " << std::endl; 
            acceptor.accept(socket);
            std::string message = make_daytime_string();
       
            boost::system::error_code ignored_error;
            boost::asio::write(socket, boost::asio::buffer(message), ignored_error);
        }
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl; 
    }
    return 0;
}
