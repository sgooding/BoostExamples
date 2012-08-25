
#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>

#include <stdlib.h>

using boost::asio::ip::tcp;

int main(int argc, char* argv[])
{
    try
    {
        // all programs require io_service
        boost::asio::io_service io_service;

        // resolves hostnames
        tcp::resolver resolver(io_service);

        tcp::resolver::query query(argv[1],"1300");
        tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
        tcp::resolver::iterator end;

        tcp::socket socket(io_service);
        boost::system::error_code error = boost::asio::error::host_not_found;
        while(error && endpoint_iterator != end)
        {
            socket.close();
            socket.connect(*endpoint_iterator++,error);
        }
        if(error)
            throw boost::system::system_error(error);

        for(;;)
        {
            boost::array<char,128> buf;
            boost::system::error_code error;
            
            // read_some will close when server closes the connection
            size_t len = socket.read_some(boost::asio::buffer(buf),error);

            if(error == boost::asio::error::eof)
                break; // connection closed cleanly by peer 
            else if(error)
                throw boost::system::system_error(error); // some other error 
            std::cout.write(buf.data(),len);
        }
    }
    catch(std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

    return EXIT_SUCCESS;
}
