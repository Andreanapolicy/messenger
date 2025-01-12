// clang-format off
#include "../pch.h"
// clang-format on
#include "ChatRoom.h"

namespace server::app
{

namespace
{
constexpr size_t MAX_RECENT_MSGS = 100;
}

void ChatRoom::Join(ChatParticipantSharedPtr participant)
{
	m_participants.insert(participant);
}

void ChatRoom::Leave(ChatParticipantSharedPtr participant)
{
	m_participants.erase(participant);
}

void ChatRoom::Deliver(const common::infrastructure::ChatMessage& msg, ChatParticipantSharedPtr sender)
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
} // namespace server::app