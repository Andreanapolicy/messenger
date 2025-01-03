#pragma once
#include "../../common/signals/Signals.h"
#include "MessageData.h"

namespace client::app
{
class IPostService
{
public:
	using NewMessageSignal = boost::signals2::signal<void(MessageData)>;
	using NewMessageSlot = NewMessageSignal::slot_type;

	virtual void SendMesssage(MessageData data) = 0;

	virtual ~IPostService() = default;
	virtual Connection DoOnNewMessage(const NewMessageSlot& handler) = 0;
};

using IPostServiceUniquePtr = std::unique_ptr<IPostService>;
} // namespace client::app