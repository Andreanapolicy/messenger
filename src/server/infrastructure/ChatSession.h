#pragma once
#include "../app/ChatRoom.h"
#include "../app/IChatSession.h"
#include <boost/asio.hpp>

namespace server::infrastructure
{
class ChatSession
	: public app::IChatSession
	, public std::enable_shared_from_this<ChatSession>
{
public:
	ChatSession(boost::asio::ip::tcp::socket socket, app::ChatRoom& room);
	
	ChatSession(const ChatSession&) = delete;
	ChatSession operator=(const ChatSession&) = delete;

	void Start() override;

	void Deliver(const common::infrastructure::ChatMessage& msg) override;

private:
	void DoReadHeader();

	void DoReadBody();

	void DoWrite();

	boost::asio::ip::tcp::socket m_socket;
	app::ChatRoom& m_room;
	common::infrastructure::ChatMessage m_currentMessage;
	common::infrastructure::ChatMessageQueue m_messageQueue;
};
} // namespace server::infrastructure