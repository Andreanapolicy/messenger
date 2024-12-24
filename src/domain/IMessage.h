#pragma once
#include "IChat_fwd.h"
#include "IMessage_fwd.h"
#include "IUser_fwd.h"

namespace domain
{
class IMessage
{
	virtual std::string GetData() const noexcept;

	virtual Time GetTime() const noexcept; /// TODO: fix

	virtual IUserSharedPtr GetAuthor() const noexcept;

	virtual IChatSharedPtr GetChat() const noexcept;
}
} // namespace domain