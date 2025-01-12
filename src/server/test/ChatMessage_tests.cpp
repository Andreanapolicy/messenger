#include "../../common/infrastructure/ChatMessage.h"
#include <gtest/gtest.h>

using namespace common::infrastructure;

TEST(ChatMessage, CreateEmptyMessage_BodySize0HeaderSize0)
{
	ChatMessage message;
	ASSERT_EQ(message.GetBodySize(), 0);
	ASSERT_EQ(message.GetSize(), 4);
}