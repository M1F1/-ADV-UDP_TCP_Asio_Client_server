#include <iostream>
// zawiera wszystkie klasy z biblioteki Asio
#include "boost/asio.hpp"
// zawiera naglowek Date_Time do "manipulacji" czasem 
#include "boost/date_time/posix_time/posix_time.hpp"
int main(){
    //  Wszystkie programy uzywające ASIO musza posiadac przynajmniej jeden
    //  obiekt typu io_service
    boost::asio::io_service io;

    // Tworzymy obiekt dostarczający funkcjonalnośc regulatora czasu (timera)
    boost::asio::deadline_timer t1 (io, boost::posix_time::seconds(3));

    // ??? Obiekt typu deadline_timer ma dwa stany: przedawniony,
    // nieprzedawniony
    // Jesli funkcja wait() jest wywolana na przedawnionym "timerze" zwróci
    // swoją wartość natychmiast. Jesto to tzw "blocking wait"
    t1.wait(); 
    std::cout << "Greetings, i was waiting for 3 sec!\n";

    boost::asio::deadline_timer t2 (io, boost::posix_time::seconds(5));
    t2.wait(); 
    std::cout << "Greetings, i was waiting for 5 sec!\n";
}

