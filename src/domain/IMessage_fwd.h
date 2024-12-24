#pragma once

namespace domain
{
class IMessage;

using IMessagePtr = std::unique_ptr<IMessage>;
using IMessageSharedPtr = std::shared_ptr<IMessage>;
} // namespace domain