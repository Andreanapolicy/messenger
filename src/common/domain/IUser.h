#pragma once
#include "IChat_fwd.h"
#include "IUser_fwd.h"
#include "UUID.h"

namespace domain
{
class IUser
{
public:
	virtual UUID GetUUID() const noexcept;

	virtual std::string GetLogin() const noexcept;

	virtual std::string GetUsername() const noexcept;

	virtual std::vector<IChatSharedPtr> GetAvailableChats() const noexcept;
}
} // namespace domain