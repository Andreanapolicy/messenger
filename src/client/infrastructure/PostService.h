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
	struct Impl;
	std::shared_ptr<Impl> m_impl;
};
} // namespace client::infrastructure