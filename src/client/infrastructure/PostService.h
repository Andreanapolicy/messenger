#pragma once
#include "../app/IPostService.h"

namespace client::infrastructure
{
class PostService final : public app::IPostService
{
public:
	PostService();

	PostService(const PostService&) = delete;
	PostService& operator=(const PostService&) = delete;

	void SendMesssage(app::MessageData data) override;
	Connection DoOnNewMessage(const NewMessageSlot& handler) override;

private:
	struct Impl;
	std::shared_ptr<Impl> m_impl;
};
} // namespace client::infrastructure