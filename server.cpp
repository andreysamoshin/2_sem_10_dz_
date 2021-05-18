#include <iostream>
#include <string>

#include <boost/asio.hpp>

std::string read_data_until(boost::asio::ip::tcp::socket & socket) 
{
	boost::asio::streambuf buffer;

	boost::asio::read_until(socket, buffer, '\n');

	std::string message;

	// Because buffer 'buf' may contain some other data
	// after '\n' symbol, we have to parse the buffer and
	// extract only symbols before the delimiter.
	std::istream input_stream(&buffer);
	std::getline(input_stream, message, '\n');

	return message;
}

int main()
{
    const std::size_t max_connections = 42;

    int port = 3333;

    boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::address_v4::any(), port);

    boost::asio::io_service io_service;

    
    try
    {
        boost::asio::ip::tcp::acceptor acceptor(io_service, endpoint.protocol());

        acceptor.bind(endpoint);

        acceptor.listen(max_connections);

        boost::asio::ip::tcp::socket socket(io_service);

        acceptor.accept(socket);

        while(true)
        {
            std::string message =  read_data_until(socket);

            if(message == "exit")
            {
                break;
            }

            std::cout << message << std::endl;
        }
    }
    catch (boost::system::system_error & e)
    {
        std::cout << "Error occured! Error code = " << e.code() << ". Message: " << e.what() << std::endl;

        system("pause");

        return e.code().value();
    }

	system("pause");

	return EXIT_SUCCESS;
}