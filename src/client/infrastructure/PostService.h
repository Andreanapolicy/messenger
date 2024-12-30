#pragma once
#include "../app/IPostService.h"

namespace client::infrastructure
{
class PostService : public app::IPostService
{
public:
	PostService();

	PostService(const PostService&) = delete;
	PostService& operator=(const PostService&) = delete;

	void SendMesssage(app::MessageData data) override;

private:
};
} // namespace client::infrastructure