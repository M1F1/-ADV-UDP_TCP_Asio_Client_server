#include <iostream>
#include <boost/asio.hpp>
#include "boost/date_time/posix_time/posix_time.hpp"
// callback handler - tworzymy funkcje ktora bedzie wywolywana w momencie
// zakonczenia asynchronicznej operacji
// ?? jako argument obiekt rzucany przez system
void print1(const boost::system::error_code& /*e*/){
    std::cout << "Greetings, i was waiting for 10 sec!\n";
}
void print2(const boost::system::error_code& /*e*/){
    std::cout << "Greetings, i was waiting for 3 sec!\n";
}
int main(){
    boost::asio::io_service io;
    boost::asio::deadline_timer t1 (io, boost::posix_time::seconds(10));
    // teraz zamiast wywoywac funkcje wait() wywolujemy f. async_wait()
    t1.async_wait(&print1);
    // mimo wywolania funkcji async_wait na t1 jestesmy w stanie przeprowadzac
    // operacje na obiekcie io, wiec tworzymy kolejny timer
    boost::asio::deadline_timer t2 (io, boost::posix_time::seconds(3));
    t2.async_wait(&print2);

    //run() -- właczą pętle procesowa danego obiektu, czyli  nastepuje wykonanie zadan
    // z ktorymi zwiazany jest obiekt - w naszym przypadku zaczynaja dzialac
    // timery. Biblioteka Asio zapewnia ze callback handlers zostana wywolane z
    // watku , ktory wlasnie wywoluje f. run(); Jesli nie wywolamy funkcji
    // run() to zwiazane z nia operacje nie zostana zrealizowane.
    io.run();
}
