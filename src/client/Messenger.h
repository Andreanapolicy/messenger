#pragma once
#include "ui/IChatView.h"
#include "ui/IMenuView.h"

namespace client
{
class Messenger
{
public:
	Messenger();
	void Start();

private:
	void OnCommand(ui::MenuCommandParams&& params);

	std::unique_ptr<ui::IChatView> m_chatView;
	std::unique_ptr<ui::IMenuView> m_menuView;
	bool m_inChat = false;
	Connection m_onCommand;
};
} // namespace client