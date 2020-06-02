#include "UDP.h"
#include <iostream>

int main()
{
	InitializeSockets();
	int handle = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	if (handle <= 0)
	{
		printf("Failed to create socket\n");
	}

	sockaddr_in address;
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons((unsigned short)7777);

	if (bind(handle, (const sockaddr*)&address, sizeof(sockaddr_in)) < 0)
	{
		printf("Failed to bind socket\n");
		return 0;
	}

	DWORD nonBlocking = 1;
	if (ioctlsocket(handle, FIONBIO, &nonBlocking) != 0)
	{
		printf("Failed to set non-blocking socket\n");
		return 0;
	}

	const char packet_data[] = "data";
	int sent_bytes = sendto(handle, packet_data, sizeof(packet_data), 0,
		(sockaddr*)&address, sizeof(sockaddr_in));

	if (sent_bytes != sizeof(packet_data))
	{
		printf("Failed to send packet: return value = %d\n", sent_bytes);
	}

    std::cout << "Hello World!\n";

	// Shutdown sockets
	WSACleanup();
}

inline bool InitializeSockets()
{
	WSADATA WsaData;
	return WSAStartup(MAKEWORD(2,2), &WsaData) == NO_ERROR;
}
