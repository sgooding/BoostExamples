#include <ctime>
#include <string>
#include <boost/asio.hpp>

#include <iostream>
#include <stdlib.h>

using boost::asio::ip::tcp;


std::string make_daytime_string()
{
    using namespace std;
    time_t now = time(0);
    return ctime(&now);
}

int main(int argc, char* argv[])
{

    try
    {
        boost::asio::io_service io_service;
        tcp::acceptor acceptor(io_service,tcp::endpoint(tcp::v4(),1300));
        for(;;)
        {
            tcp::socket socket(io_service);
            acceptor.accept(socket);

            std::string message = make_daytime_string();

            boost::system::error_code ignored_error;
            boost::asio::write(socket,boost::asio::buffer(message),
                    boost::asio::transfer_all(), ignored_error);
        }
    }
    catch(std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }


    return EXIT_SUCCESS;
}
