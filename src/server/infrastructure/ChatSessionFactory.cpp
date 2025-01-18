// clang-format off
#include "../pch.h"
// clang-format on
#include "ChatSessionFactory.h"
#include "ChatSession.h"

using boost::asio::ip::tcp;

namespace server::infrastructure
{
app::IChatSessionSharedPtr ChatSessionFactory::CreateChatSession(
	boost::asio::ip::tcp::socket socket,
	app::ChatRoom& room)
{
	return std::make_shared<ChatSession>(std::move(socket), room);
}
}