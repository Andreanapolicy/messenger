#pragma once
#include "MessageData.h"

namespace client::app
{
class IPostService
{
public:
	virtual void SendMesssage(MessageData data) = 0;

	virtual ~IPostService() = default;
};

using IPostServiceUniquePtr = std::unique_ptr<IPostService>;
} // namespace client::app