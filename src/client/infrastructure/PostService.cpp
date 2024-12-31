// clang-format off
#include "../pch.h"
// clang-format on
#include "PostService.h"
#include <iostream> // todo: delete

#include <cstring>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

namespace client::infrastructure
{
PostService::PostService()
{
}

void PostService::SendMesssage(app::MessageData data)
{
	// creating socket
	int clientSocket = socket(AF_INET, SOCK_STREAM, 0);

	// specifying address
	sockaddr_in serverAddress;
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(8080);
	serverAddress.sin_addr.s_addr = INADDR_ANY;

	// sending connection request
	connect(clientSocket, (struct sockaddr*)&serverAddress,
		sizeof(serverAddress));

	// sending data
	send(clientSocket, data.data.c_str(), data.data.size(), 0);

	// closing socket
	close(clientSocket);
}
} // namespace client::infrastructure