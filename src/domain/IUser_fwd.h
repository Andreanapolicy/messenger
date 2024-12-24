#pragma once

namespace domain
{
class IUser;

using IUserPtr = std::unique_ptr<IUser>;
using IUserSharedPtr = std::shared_ptr<IUser>;
} // namespace domain