#include <memory>
#include <set>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "../app/ChatRoom.h"

using namespace server::app;
using common::infrastructure::ChatMessage;

class MockChatParticipant final : public ChatParticipant
{
public:
	MOCK_METHOD(void, Deliver, (const ChatMessage&), (override));
};

class ChatRoomTest : public testing::Test
{
protected:
	~ChatRoomTest() override = default;

	void SetUp() override
	{
	}

	void TearDown() override {}

	ChatRoom chatRoom;

	ChatParticipantSharedPtr user1 = std::make_shared<MockChatParticipant>();
	ChatParticipantSharedPtr user2 = std::make_shared<MockChatParticipant>();
	ChatParticipantSharedPtr user3 = std::make_shared<MockChatParticipant>();
	ChatParticipantSharedPtr user4 = std::make_shared<MockChatParticipant>();
	ChatMessage message;
};

TEST_F(ChatRoomTest, EmptyRoomHas0Participants)
{
	ASSERT_EQ(chatRoom.GetParticipantsCount(), 0);
}

TEST_F(ChatRoomTest, AddToRoomParticipants_ParticipantsCountWillBe2)
{
	chatRoom.Join(user1);
	chatRoom.Join(user2);

	ASSERT_EQ(chatRoom.GetParticipantsCount(), 2);
}

TEST_F(ChatRoomTest, AddToRoomAlreadyJoinedParticipants_ParticipantsCountWillNotBeChanged)
{
	chatRoom.Join(user1);
	chatRoom.Join(user1);
	
	ASSERT_EQ(chatRoom.GetParticipantsCount(), 1);
}

TEST_F(ChatRoomTest, LeaveFromRoom_ParticipantsCountWillDecrease)
{
	chatRoom.Join(user1);
	chatRoom.Join(user2);
	
	chatRoom.Leave(user2);

	ASSERT_EQ(chatRoom.GetParticipantsCount(), 1);
}

TEST_F(ChatRoomTest, NonExistingPartisipantLeavesFromRoom_ParticipantsCountWillNotBeChanged)
{
	chatRoom.Join(user1);
	chatRoom.Join(user2);
	
	chatRoom.Leave(user3);

	ASSERT_EQ(chatRoom.GetParticipantsCount(), 2);
}

TEST_F(ChatRoomTest, DeliverMessageToNobody_ParticipantsWillNotBeNotificated)
{
	chatRoom.Deliver(message, user1);

	EXPECT_CALL(user1, Deliver(message)).Times(0);
	EXPECT_CALL(user2, Deliver(message)).Times(0);
	EXPECT_CALL(user3, Deliver(message)).Times(0);
	EXPECT_CALL(user4, Deliver(message)).Times(0);
}