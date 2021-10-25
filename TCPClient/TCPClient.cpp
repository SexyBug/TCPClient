#include <iostream>
#include "Poco/Net/StreamSocket.h"
#include "Poco/Net/SocketAddress.h"

//TCP接收缓冲区大小
#define BUFFER_SIZE 1024
//单次连接接收数据最大长度
#define MAX_DATA_SIZE 1024*10

using Poco::Net::SocketAddress;
using Poco::Net::StreamSocket;
using Poco::Exception;

//接收服务器单次发送的数据
int receiveAll(StreamSocket socket,char* data,int* dataLength) {
	*dataLength = 0;
	char buffer[BUFFER_SIZE];
	
	/// Returns the number of bytes received.
	/// A return value of 0 means a graceful shutdown
	/// of the connection from the peer.
	int n = socket.receiveBytes(buffer, sizeof(buffer));
	while (n > 0)
	{
		memcpy_s(data+(*dataLength),MAX_DATA_SIZE,buffer,n);
		*dataLength += n;
		n = socket.receiveBytes(buffer, sizeof(buffer));
	}
	return 0;
}

int main(int argc, const char* argv[])
{
	SocketAddress address("127.0.0.1", 9911);
	
	try
	{
		StreamSocket socket(address);
		char* data = new char[MAX_DATA_SIZE];
		int dataLength = 0;
		receiveAll(socket, data, &dataLength);
		data[dataLength] = '\0';
		std::cout << data << std::endl;
	}
	catch (Exception& exc)
	{
		std::cerr << "ClientConnection: " << exc.displayText() << std::endl;
	}
	return 0;
}