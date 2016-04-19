#include <iostream>
#include "boost/asio.hpp"
#include "boost/bind.hpp"
#include "boost/date_time/posix_time/posix_time.hpp"
// modyfikacja poprzedniego programy, tak aby timer pokazywal uplywajace
// sekundy.
// Do tego zadania uzyjemy funkcji std::bind, poniewaz async_wait oczekuje
// funkcji lub obiektu funkcyjnego z sygnatura (lista argumentow)
// void (const boost::system::error_code &). wiazanie dodatkowych parametrow
// "konwertuje" funkcje do tej odpowiadajacej sygnaturze async_wait
// aby tego dokonac musimy zmieniac czas przedawnienia timera w callback
// handler i zaczynac asyn_wait. Oznacza to oczywiscie ze nasz callback
// function musi miec dostep do  obiektu timera, 
// a wiec do argumetow naszego handlera dodajemy wskaznik na obiekt timera
// oraz licznik tak, abysmy mogli zakonczyc rekurencje (base case) 
//
//
// w momencie zakonczenia async_wait wywolany jest callback handler, ktory
// rowniez rozpoczyna async_wait , a przez to ze jest to asyncwait to zadania
// te wykonywane sa niezaleznie od siebie 
void print(const boost::system::error_code& /*e*/,
    boost::asio::deadline_timer* t, int* count)
{ // base case
  if (*count < 5)
  {
    std::cout << *count << std::endl;
    ++(*count);

    t->expires_at(t->expires_at() + boost::posix_time::seconds(1));
    t->async_wait(boost::bind(print,
          boost::asio::placeholders::error, t, count));
  }
}

int main()
{
  boost::asio::io_service io;

  int count = 0;
  boost::asio::deadline_timer t(io, boost::posix_time::seconds(1));
  t.async_wait(boost::bind(print, boost::asio::placeholders::error, &t, &count));

  io.run();
  //  funkcja konczy dzialanie w momencie gdy "nie ma nic wiecej do zrobienia"

  std::cout << "Final count is " << count << std::endl;

  return 0;
}
