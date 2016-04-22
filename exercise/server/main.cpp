#include <iostream>
#include "Harness.h"
using boost::asio::ip::tcp;

int main(){

   Input_Output_con io_con =  Input_Output_con();

   boost::asio::io_service io_service;

   InputOutputTCP io_tcp = InputOutputTCP(io_service, 1241);

   Input_Output_Proxy players_outputs = Input_Output_Proxy();
   players_outputs.register_output(&io_con);
   players_outputs.register_output(&io_tcp);

    Input_Output_Interface* players_inputs[2] {&io_con, &io_tcp};

   Harness* h = new Harness(&players_outputs, players_inputs);
   h->Start();
   delete h;
}
