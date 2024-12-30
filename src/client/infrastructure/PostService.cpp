#include "PostService.h"
#include "../pch.h"
#include <iostream> // todo: delete

namespace client::infrastructure
{
PostService::PostService()
{
}

void PostService::SendMesssage(app::MessageData data)
{
	std::cout << "message " << data.data << " was sent" << std::endl;
}
} // namespace client::infrastructure