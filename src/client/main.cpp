#include "pch.h"
#include "Messenger.h"
#include "infrastructure/PostService.h"
#include <iostream>

int main()
{
	std::cout << "This is client app" << std::endl;
	auto postService = std::make_unique<client::infrastructure::PostService>();
	client::Messenger messenger{ std::move(postService), std::cout };
	messenger.Start();

	return 0;
}