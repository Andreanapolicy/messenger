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
	std::unique_ptr<ui::IChatView> m_chatView;
	std::unique_ptr<ui::IMenuView> m_menuView;
};
} // namespace client