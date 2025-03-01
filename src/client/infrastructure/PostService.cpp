// clang-format off
#include "../pch.h"
// clang-format on
#include "PostService.h"
#include "../../common/infrastructure/ChatMessage.h"
#include "../../common/infrastructure/ServerSettings.h"
#include "../../common/proto/include.h"
#include <boost/asio.hpp>
#include <cstdlib>
#include <deque>
#include <iostream>
#include <optional>
#include <thread>

namespace client::infrastructure
{

using boost::asio::ip::tcp;
using namespace common::infrastructure;
using common::infrastructure::ChatMessage;

using ChatMessageQueue = std::deque<ChatMessage>;

class Client final
{
public:
	Client(boost::asio::io_context& ioContext,
		tcp::resolver::iterator endpointIterator)
		: m_ioContext(ioContext)
		, m_socket(ioContext)
	{
		DoConnect(endpointIterator);
	}

	void Write(const ChatMessage& msg)
	{
		boost::asio::post(m_ioContext, [this, msg]() {
			bool write_in_progress = !m_messageQueue.empty();
			m_messageQueue.push_back(msg);
			if (!write_in_progress)
			{
				DoWrite();
			}
		});
	}

	void Close()
	{
		m_ioContext.post([this]() { m_socket.close(); });
	}

	Connection DoOnNewMessage(const PostService::NewMessageSlot& handler)
	{
		return m_onNewMessage.connect(handler);
	}

private:
	void DoConnect(tcp::resolver::iterator endpointIterator)
	{
		boost::asio::async_connect(
			m_socket, endpointIterator,
			[this](boost::system::error_code ec, tcp::resolver::iterator) {
				if (!ec)
				{
					DoReadHeader();
				}
			});
	}

	void DoReadHeader()
	{
		boost::asio::async_read(
			m_socket,
			boost::asio::buffer(m_newMessage.GetData(), ChatMessage::HEADER_LENGTH),
			[this](boost::system::error_code ec, std::size_t /*length*/) {
				if (!ec && m_newMessage.DecodeHeader())
				{
					DoReadBody();
				}
				else
				{
					m_socket.close();
				}
			});
	}

	void DoReadBody()
	{
		boost::asio::async_read(
			m_socket,
			boost::asio::buffer(m_newMessage.GetBody(), m_newMessage.GetBodySize()),
			[this](boost::system::error_code ec, std::size_t /*length*/) {
				if (!ec)
				{
					messenger_proto::Message msg;
					msg.ParseFromString(m_newMessage.GetBody());
					m_onNewMessage({ msg.fromusername(), msg.data() });
					DoReadHeader();
				}
				else
				{
					m_socket.close();
				}
			});
	}

	void DoWrite()
	{
		boost::asio::async_write(
			m_socket,
			boost::asio::buffer(m_messageQueue.front().GetData(),
				m_messageQueue.front().GetSize()),
			[this](boost::system::error_code ec, std::size_t /*length*/) {
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
					m_socket.close();
				}
			});
	}

private:
	boost::asio::io_context& m_ioContext;
	tcp::socket m_socket;
	ChatMessage m_newMessage;
	ChatMessageQueue m_messageQueue;
	PostService::NewMessageSignal m_onNewMessage;
};

struct PostService::Impl
{
public:
	Impl()
		: m_client{ m_ioContext, tcp::resolver{ m_ioContext }.resolve({ SERVER_HOST, std::to_string(SERVER_PORT) }) }
		, m_thread{ [&]() { m_ioContext.run(); } }
	{
	}

	~Impl()
	{
		m_client.Close();
		m_thread.join();
	}

	Connection DoOnNewMessage(const NewMessageSlot& handler)
	{
		return m_client.DoOnNewMessage(handler);
	}

	void SendMesssage(app::MessageData data)
	{
		ChatMessage msg;
		messenger_proto::Message message;
		message.set_data(data.data);
		message.set_fromusername(data.from);
		auto sendingData = message.SerializeAsString();

		msg.SetBodySize(sendingData.size());
		std::memcpy(msg.GetBody(), sendingData.c_str(), msg.GetBodySize());
		msg.EncodeHeader();

		m_client.Write(msg);
	}

private:
	boost::asio::io_context m_ioContext;
	Client m_client;
	std::thread m_thread;
};

PostService::PostService()
	: m_impl{ std::make_shared<Impl>() }
{
}

void PostService::SendMesssage(app::MessageData data)
{
	m_impl->SendMesssage(std::move(data));
}

Connection PostService::DoOnNewMessage(const NewMessageSlot& handler)
{
	return m_impl->DoOnNewMessage(handler);
}
} // namespace client::infrastructure