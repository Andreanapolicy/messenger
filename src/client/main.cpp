#include "pch.h"
#include "Messenger.h"
#include "infrastructure/PostService.h"
#include <iostream>

int main(int argc, char** argv)
{
	if (argc != 2)
	{
		std::cout << "Error, use `client <you_name>`" << std::endl;
		return 1;
	}

	std::string clientName = argv[1];
	std::cout << "This is client app" << std::endl;
	auto postService = std::make_unique<client::infrastructure::PostService>();
	client::Messenger messenger{ std::move(postService), std::cout, std::move(clientName) };
	messenger.Start();

	return 0;
}