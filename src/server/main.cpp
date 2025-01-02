#include "../common/infrastructure/ChatMessage.h"
#include <boost/asio.hpp>
#include <cstdlib>
#include <deque>
#include <iostream>
#include <list>
#include <memory>
#include <set>
#include <utility>

using boost::asio::ip::tcp;
using common::infrastructure::ChatMessage;

using ChatMessageQueue = std::deque<ChatMessage>;

class ChatParticipant
{
public:
	virtual ~ChatParticipant() {}
	virtual void Deliver(const ChatMessage& msg) = 0;
};

typedef std::shared_ptr<ChatParticipant> ChatParticipant_ptr;

class ChatRoom
{
public:
	void Join(ChatParticipant_ptr participant)
	{
		m_participants.insert(participant);
		for (auto msg : m_messageQueue)
			participant->Deliver(msg);
	}

	void Leave(ChatParticipant_ptr participant)
	{
		m_participants.erase(participant);
	}

	void Deliver(const ChatMessage& msg)
	{
		m_messageQueue.push_back(msg);
		while (m_messageQueue.size() > max_recent_msgs)
			m_messageQueue.pop_front();

		for (auto participant : m_participants)
			participant->Deliver(msg);
	}

private:
	std::set<ChatParticipant_ptr> m_participants;
	enum
	{
		max_recent_msgs = 100
	};
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
		bool write_in_progress = !m_messageQueue.empty();
		m_messageQueue.push_back(msg);
		if (!write_in_progress)
		{
			DoWrite();
		}
	}

private:
	void DoReadHeader()
	{
		auto self(shared_from_this());
		boost::asio::async_read(m_socket,
			boost::asio::buffer(m_currentMessage.GetData(), ChatMessage::HEADER_LENGTH),
			[this, self](boost::system::error_code ec, std::size_t /*length*/) {
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
		auto self(shared_from_this());
		boost::asio::async_read(m_socket,
			boost::asio::buffer(m_currentMessage.GetBody(), m_currentMessage.GetBodySize()),
			[this, self](boost::system::error_code ec, std::size_t /*length*/) {
				if (!ec)
				{
					m_room.Deliver(m_currentMessage);
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
			[this, self](boost::system::error_code ec, std::size_t /*length*/) {
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
		do_accept();
	}

private:
	void do_accept()
	{
		m_acceptor.async_accept(m_socket,
			[this](boost::system::error_code ec) {
				if (!ec)
				{
					std::make_shared<ChatSession>(std::move(m_socket), m_room)->Start();
				}

				do_accept();
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

		ChatServer servers{ ioContext, tcp::endpoint{ tcp::v4(), 8080 } };

		ioContext.run();
	}
	catch (std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << "\n";
	}

	return 0;
}
