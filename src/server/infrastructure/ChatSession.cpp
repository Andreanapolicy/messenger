// clang-format off
#include "../pch.h"
// clang-format on
#include "ChatSession.h"

using boost::asio::ip::tcp;

namespace server::infrastructure
{

ChatSession::ChatSession(tcp::socket socket, app::ChatRoom& room)
	: m_socket(std::move(socket))
	, m_room(room)
{
}

void ChatSession::Deliver(const common::infrastructure::ChatMessage& msg)
{
	bool WriteInProgress = !m_messageQueue.empty();
	m_messageQueue.push_back(msg);
	if (!WriteInProgress)
	{
		DoWrite();
	}
}

void ChatSession::Start()
{
	m_room.Join(shared_from_this());
	DoReadHeader();
}

void ChatSession::DoWrite()
{
	auto self(shared_from_this());
	boost::asio::async_write(m_socket,
		boost::asio::buffer(m_messageQueue.front().GetData(),
			m_messageQueue.front().GetSize()),
		[this, self](boost::system::error_code ec, std::size_t) {
			if (!ec)
			{
				m_messageQueue.pop_front();
				if (!m_messageQueue.empty())
				{
					DoWrite();
				}
			}
			else
			{
				m_room.Leave(shared_from_this());
			}
		});
}

void ChatSession::DoReadBody()
{
	auto self{ shared_from_this() };
	boost::asio::async_read(m_socket,
		boost::asio::buffer(m_currentMessage.GetBody(), m_currentMessage.GetBodySize()),
		[this, self](boost::system::error_code ec, std::size_t) {
			if (!ec)
			{
				m_room.Deliver(m_currentMessage, self);
				DoReadHeader();
			}
			else
			{
				m_room.Leave(shared_from_this());
			}
		});
}

void ChatSession::DoReadHeader()
{
	auto self{ shared_from_this() };
	boost::asio::async_read(m_socket,
		boost::asio::buffer(m_currentMessage.GetData(), common::infrastructure::ChatMessage::HEADER_LENGTH),
		[this, self](boost::system::error_code ec, std::size_t) {
			if (!ec && m_currentMessage.DecodeHeader())
			{
				DoReadBody();
			}
			else
			{
				m_room.Leave(shared_from_this());
			}
		});
}
} // namespace server::infrastructure