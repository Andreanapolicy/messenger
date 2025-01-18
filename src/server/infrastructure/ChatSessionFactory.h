#pragma once
#include "../app/ChatRoom.h"
#include "../app/IChatSession.h"
#include <boost/asio.hpp>

namespace server::infrastructure
{
class ChatSessionFactory final
{
public:
	static app::IChatSessionSharedPtr CreateChatSession(
		boost::asio::ip::tcp::socket socket,
		app::ChatRoom& room);
	
};
} // namespace server::infrastructure