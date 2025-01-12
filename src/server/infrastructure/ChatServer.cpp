// clang-format off
#include "../pch.h"
// clang-format on
#include "ChatServer.h"
#include "ChatSession.h"

namespace server::infrastructure
{

ChatServer::ChatServer(boost::asio::io_context& ioContext,
	const boost::asio::ip::tcp::endpoint& endpoint)
	: m_acceptor(ioContext, endpoint)
	, m_socket(ioContext)
{
	DoAccept();
}

void ChatServer::DoAccept()
{
	m_acceptor.async_accept(m_socket,
		[this](boost::system::error_code ec) {
			if (!ec)
			{
				std::make_shared<infrastructure::ChatSession>(std::move(m_socket), m_room)->Start();
			}

			DoAccept();
		});
}
}; // namespace server::infrastructure