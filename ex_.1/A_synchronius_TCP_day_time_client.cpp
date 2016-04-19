// celem tej aplikacji jest dostep do daytime service, a wiec 
// a wiec  uzytkownik musi wskazac serwer
//
#include <iostream>
#include "boost/array.hpp"
#include "boost/asio.hpp"

using boost::asio::ip::tcp;
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
   // musimy zamienic nazwe serwera ktora zostala wskazana jako parametr do
   // aplikacji, na TCP punk koncowy. Aby tego dokonac uzywamy
   // ip::tcp::resolver obiekt
           tcp::resolver resolver(io_service);
           // resolver przyjmuje querry object i zamienia go na liste punktow
           // dostepowych do serwisow. tworzymy query  uzywjac nazwy serwera
           // oraz nazwe uslugi
           tcp::resolver::query query(argv[1], argv[2]);
           // lista punktow dostepowych  jest zwracana w formie iteratora typu
           // ip::tcp::resolver::iterator
           tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
           // teraz tworzymy i podlaczamy socket.  Lista punktow dostepowych
           // uzyskanych powyzej zawieraja ipv4 jak i ipv6 punkty dostepowe
           // wiec musiym sprobowac kazde z nich za nim znajdziemy to ktore
           // dziala. To sprawia ze client program jest niezalezny od wersji
           // ip . Funkcja boost::asio::connect() robi to za nas automatycznie
           tcp::socket socket(io_service);
           boost::asio::connect(socket, endpoint_iterator);
           // polaczenie jest otwarte , teraz pozostalo nam odczytac odpowiedz
           //  protokolu daytime
           // uzywamy boost::array aby zapisac otrzymane dane. Funkcja
           // boost::asio::buffer() automatycznie determinuje rozmiar tablicy
           // aby zabezpieczyc przed przeciazeniem
           for(;;)
           {
              boost::array<char, 128> buf;
              boost::system::error_code error;
              size_t len = socket.read_some(boost::asio::buffer(buf), error);
                //  kiedy serwer zakonczy polaczenie
                //  ip::tcp::socket::read_some()  zakonczy dzialanie z
                //  boost::asio::error:eof error, wiec dzieki temu wiemy jak
                //  zakonczyc petle;
              if (error == boost::asio::error::eof)
                  break;
              else if (error)
                  throw boost::system::system_error(error); // inny blad

              std::cout.write(buf.data(), len);
           }
       }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

}
