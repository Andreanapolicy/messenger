#include "pch.h"
#include "Messenger.h"
#include "ui/ChatView.h"
#include "ui/MenuView.h"
#include <iostream>

namespace client
{
Messenger::Messenger()
	: m_chatView{ std::make_unique<ui::ChatView>() }
	, m_menuView{ std::make_unique<ui::MenuView>() }
{
	m_onCommand = m_menuView->DoOnCommand(std::bind_front(&Messenger::OnCommand, this));
}

void Messenger::Start()
{
	while (m_menuView)
	{
		m_menuView->HandleCommand();
	}
}

void Messenger::OnCommand(ui::MenuCommandParams&& params)
{
	// TODO: do some actions
	std::cout << "command " << static_cast<int>(params.GetCommand()) << " and data " << params.GetData() << std::endl;
}
} // namespace client