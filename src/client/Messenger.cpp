#include "pch.h"
#include "Messenger.h"
#include "ui/ChatView.h"
#include "ui/MenuView.h"
#include <iostream>

namespace client
{
Messenger::Messenger(app::IPostServiceUniquePtr postService)
	: m_chatView{ std::make_unique<ui::ChatView>() }
	, m_menuView{ std::make_unique<ui::MenuView>() }
	, m_postService{ std::move(postService) }
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
		std::cout << "!> you opened chat" << std::endl;
		break;
	case ui::MenuCommand::Message:
		m_postService->SendMesssage(app::MessageData{ params.GetData() });
		break;
	case ui::MenuCommand::Unknown:
	default:
		std::cout << "!> now a command. Use <:help>" << std::endl;
		break;
	}
}
} // namespace client