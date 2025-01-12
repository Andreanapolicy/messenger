#pragma once
#include "ChatParticipant.h"

namespace server::app
{
class IChatSession : public ChatParticipant
{
public:
	virtual void Start() = 0;

	virtual ~IChatSession() = default;
};
} // namespace server::app