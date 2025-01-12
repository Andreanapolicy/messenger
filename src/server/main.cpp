#include "pch.h"
#include "../common/infrastructure/ServerSettings.h"
#include "infrastructure/ChatServer.h"
#include <boost/asio.hpp>
#include <iostream>

int main()
{
	try
	{
		boost::asio::io_context ioContext;

		server::infrastructure::ChatServer servers{
			ioContext,
			boost::asio::ip::tcp::endpoint{
				boost::asio::ip::tcp::v4(),
				common::infrastructure::SERVER_PORT }
		};

		ioContext.run();
	}
	catch (const std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << "\n";
	}

	return 0;
}
