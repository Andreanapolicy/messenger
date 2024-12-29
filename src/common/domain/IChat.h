#pragma once
#include "IChat_fwd.h"
#include "UUID.h"

namespace domain
{
class IChat
{
public:
	virtual UUID GetUUID() const noexcept;

	virtual std::vector<IUserSharedPtr> GetUsers() const noexcept;
}
} // namespace domain