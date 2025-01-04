#include "../common/infrastructure/ChatMessage.h"
#include "../common/infrastructure/ServerSettings.h"
#include <boost/asio.hpp>
#include <cstdlib>
#include <deque>
#include <iostream>
#include <list>
#include <memory>
#include <set>
#include <utility>

using boost::asio::ip::tcp;
using namespace common::infrastructure;

using ChatMessageQueue = std::deque<ChatMessage>;

class ChatParticipant
{
public:
	virtual ~ChatParticipant() = default;
	virtual void Deliver(const ChatMessage& msg) = 0;
};

typedef std::shared_ptr<ChatParticipant> ChatParticipantSharedPtr;

class ChatRoom
{
public:
	static const int MAX_RECENT_MSGS = 100;

	void Join(ChatParticipantSharedPtr participant)
	{
		m_participants.insert(participant);
	}

	void Leave(ChatParticipantSharedPtr participant)
	{
		m_participants.erase(participant);
	}

	void Deliver(const ChatMessage& msg, ChatParticipantSharedPtr sender)
	{
		m_messageQueue.push_back(msg);
		while (m_messageQueue.size() > MAX_RECENT_MSGS)
		{
			m_messageQueue.pop_front();
		}

		for (auto participant : m_participants)
		{
			if (participant == sender)
			{
				continue;
			}
			participant->Deliver(msg);
		}
	}

private:
	std::set<ChatParticipantSharedPtr> m_participants;
	ChatMessageQueue m_messageQueue;
};

class ChatSession
	: public ChatParticipant
	, public std::enable_shared_from_this<ChatSession>
{
public:
	ChatSession(tcp::socket socket, ChatRoom& room)
		: m_socket(std::move(socket))
		, m_room(room)
	{
	}

	void Start()
	{
		m_room.Join(shared_from_this());
		DoReadHeader();
	}

	void Deliver(const ChatMessage& msg)
	{
		bool WriteInProgress = !m_messageQueue.empty();
		m_messageQueue.push_back(msg);
		if (!WriteInProgress)
		{
			DoWrite();
		}
	}

private:
	void DoReadHeader()
	{
		auto self{ shared_from_this() };
		boost::asio::async_read(m_socket,
			boost::asio::buffer(m_currentMessage.GetData(), ChatMessage::HEADER_LENGTH),
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

	void DoReadBody()
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

	void DoWrite()
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

	tcp::socket m_socket;
	ChatRoom& m_room;
	ChatMessage m_currentMessage;
	ChatMessageQueue m_messageQueue;
};

class ChatServer
{
public:
	ChatServer(boost::asio::io_context& ioContext,
		const tcp::endpoint& endpoint)
		: m_acceptor(ioContext, endpoint)
		, m_socket(ioContext)
	{
		DoAccept();
	}

private:
	void DoAccept()
	{
		m_acceptor.async_accept(m_socket,
			[this](boost::system::error_code ec) {
				if (!ec)
				{
					std::make_shared<ChatSession>(std::move(m_socket), m_room)->Start();
				}

				DoAccept();
			});
	}

	tcp::acceptor m_acceptor;
	tcp::socket m_socket;
	ChatRoom m_room; // Один сервер - один чат. Чтобы сделать несколько чатов на одном сервере - нужно сделать вектор чатов.
};

int main()
{
	try
	{
		boost::asio::io_context ioContext;

		ChatServer servers{ ioContext, tcp::endpoint{ tcp::v4(), SERVER_PORT } };

		ioContext.run();
	}
	catch (const std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << "\n";
	}

	return 0;
}
