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
	switch (params.GetCommand())
	{
	case ui::MenuCommand::Exit:
		m_menuView.reset();
		break;
	case ui::MenuCommand::ShowChats:
		std::cout << "!> show-chats now is not available" << std::endl;
		break;
	case ui::MenuCommand::OpenChat:
		std::cout << "!> open-chat now is not available" << std::endl;
		break;
	default:
		std::cout << "!> now a command. Use <:help>" << std::endl;
		break;
	}
}
} // namespace client