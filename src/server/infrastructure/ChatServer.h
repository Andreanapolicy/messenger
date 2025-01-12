#pragma once
#include "../app/ChatRoom.h"
#include <boost/asio.hpp>

namespace server::infrastructure
{
class ChatServer final
{
public:
	ChatServer(boost::asio::io_context& ioContext, const boost::asio::ip::tcp::endpoint& endpoint);

	ChatServer(const ChatServer&) = delete;
	ChatServer operator=(const ChatServer&) = delete;

private:
	void DoAccept();

	boost::asio::ip::tcp::acceptor m_acceptor;
	boost::asio::ip::tcp::socket m_socket;
	app::ChatRoom m_room;
};
} // namespace server::infrastructure