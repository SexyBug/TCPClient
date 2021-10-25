#include <iostream>
#include "Poco/Net/StreamSocket.h"
#include "Poco/Net/SocketAddress.h"

//最大接收数据长度
#define BUFFER_SIZE 10240

using Poco::Net::SocketAddress;
using Poco::Net::StreamSocket;
using Poco::Exception;

int main(int argc, const char* argv[])
{
	SocketAddress address("127.0.0.1", 9911);
	
	try
	{
		StreamSocket socket(address);

		socket.sendBytes("qqq",3);
		socket.sendBytes("www", 3);
		//Sleep(10000);
		unsigned char* buffer = new unsigned char[BUFFER_SIZE];
		/// Returns the number of bytes received.
		/// A return value of 0 means a graceful shutdown
		/// of the connection from the peer.
		int n = socket.receiveBytes(buffer, BUFFER_SIZE);
		buffer[n] = '\0';
		std::cout << "Server Message: " << std::endl;
		std::cout << n << std::endl;
		std::cout << buffer << std::endl;
	}
	catch (Exception& exc)
	{
		std::cerr << "TCPClient: " << exc.displayText() << std::endl;
	}
	return 0;
}