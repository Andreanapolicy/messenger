#include "pch.h"
#include "Messenger.h"
#include <iostream>

int main()
{
	std::cout << "This is client app" << std::endl;
	client::Messenger messenger;
	messenger.Start();

	return 0;
}