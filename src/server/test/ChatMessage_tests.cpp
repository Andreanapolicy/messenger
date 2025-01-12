#include "../../common/infrastructure/ChatMessage.h"
#include <cstring>
#include <gtest/gtest.h>

using namespace common::infrastructure;

TEST(ChatMessage, CreateEmptyMessage_BodySize0HeaderSize4)
{
	ChatMessage message;
	ASSERT_EQ(message.GetBodySize(), 0);
	ASSERT_EQ(message.GetSize(), 4);
}

TEST(ChatMessage, CreateNotEmptyMessage_BodySize9HeaderSize4)
{
	ChatMessage message;
	const std::string data = "hello";
	message.SetBodySize(data.size());
	std::memcpy(message.GetBody(), data.c_str(), message.GetBodySize());
	message.EncodeHeader();
	auto msg = message.GetData();

	ASSERT_EQ(message.GetBodySize(), 5);
	ASSERT_EQ(message.GetSize(), 9);
	ASSERT_EQ(std::string{ msg }, "   5hello");
}

TEST(ChatMessage, Create1025CharsMessage_MessageWillBeOnly1024)
{
	ChatMessage message;
	const std::string data(1025, '0');
	message.SetBodySize(data.size());
	std::memcpy(message.GetBody(), data.c_str(), message.GetBodySize());
	message.EncodeHeader();

	ASSERT_EQ(message.GetBodySize(), 1024);
}

TEST(ChatMessage, Create1024CharsMessage_MessageWillBe1024)
{
	ChatMessage message;
	const std::string data(1024, '0');
	message.SetBodySize(data.size());
	std::memcpy(message.GetBody(), data.c_str(), message.GetBodySize());
	message.EncodeHeader();

	ASSERT_EQ(message.GetBodySize(), 1024);
}