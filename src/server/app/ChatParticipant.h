#pragma once
#include "../../common/infrastructure/ChatMessage.h"

namespace server::app
{
class ChatParticipant
{
public:
	virtual void Deliver(const common::infrastructure::ChatMessage& msg) = 0;

	virtual ~ChatParticipant() = default;
};

using ChatParticipantSharedPtr = std::shared_ptr<ChatParticipant>;

} // namespace server::app