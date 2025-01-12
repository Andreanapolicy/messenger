#pragma once
#include "ChatParticipant.h"

namespace server::app
{
class ChatRoom
{
public:
	void Join(ChatParticipantSharedPtr participant);

	void Leave(ChatParticipantSharedPtr participant);

	void Deliver(const common::infrastructure::ChatMessage& msg, ChatParticipantSharedPtr sender);

private:
	std::set<ChatParticipantSharedPtr> m_participants;
	common::infrastructure::ChatMessageQueue m_messageQueue;
};
} // namespace server::app