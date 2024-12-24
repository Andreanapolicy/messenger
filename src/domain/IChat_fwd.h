#pragma once

namespace domain
{
class IChat;

using IChatPtr = std::unique_ptr<IChat>;
using IChatSharedPtr = std::shared_ptr<IChat>;
} // namespace domain