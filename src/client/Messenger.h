#pragma once
#include "app/IPostService.h"
#include "ui/IChatView.h"
#include "ui/IMenuView.h"

namespace client
{
class Messenger
{
public:
	explicit Messenger(app::IPostServiceUniquePtr postService);
	void Start();

private:
	void OnCommand(ui::MenuCommandParams&& params);
	void OnNewMessage(app::MessageData&& message);

	std::unique_ptr<ui::IChatView> m_chatView;
	std::unique_ptr<ui::IMenuView> m_menuView;
	std::array<Connection, 2> m_connections;
	app::IPostServiceUniquePtr m_postService;
};
} // namespace client