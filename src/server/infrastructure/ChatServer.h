#pragma once
#include "../app/ChatRoom.h"
#include <boost/asio.hpp>

namespace server::infrastructure
{
class ChatServer
{
public:
	ChatServer(boost::asio::io_context& ioContext, const boost::asio::ip::tcp::endpoint& endpoint);

private:
	void DoAccept();

	boost::asio::ip::tcp::acceptor m_acceptor;
	boost::asio::ip::tcp::socket m_socket;
	app::ChatRoom m_room;
};
} // namespace server::infrastructure