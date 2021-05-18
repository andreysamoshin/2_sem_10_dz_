#include <iostream>
#include <string>

#include <boost/asio.hpp>

int main()
{
    std::string localhost_raw = "127.0.0.1"; // my IP address

    int port = 3333;

    std::string username;

    std::cout << "Enter your name: ";
    std::getline(std::cin, username);

    try
    {
        boost::asio::ip::tcp::endpoint endpoint (
            boost::asio::ip::address::from_string(localhost_raw), port);
        
        boost::asio::io_service io_service;

        boost::asio::ip::tcp::socket socket(io_service, endpoint.protocol());

        socket.connect(endpoint);

        while(true)
        {
            std::string message;

            std::getline(std::cin, message);

            message = username + ": " + message + '\n';

            boost::asio::write(socket, boost::asio::buffer(message.c_str(), message.length()));
        }
        
    }
    catch(const boost::system::system_error& e)
    {
		std::cout << "Error occured! Error code = " << e.code() << ". Message: " << e.what() << std::endl;

		system("pause");

		return e.code().value();
	}

	system("pause");

	return EXIT_SUCCESS;
}