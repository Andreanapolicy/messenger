#include "pch.h"
#include "Messenger.h"
#include "ui/ChatView.h"
#include "ui/MenuView.h"

namespace client
{
Messenger::Messenger(app::IPostServiceUniquePtr postService, std::ostream& output)
	: m_output{ output }
	, m_chatView{ std::make_unique<ui::ChatView>(m_output) }
	, m_menuView{ std::make_unique<ui::MenuView>(m_output) }
	, m_postService{ std::move(postService) }
{
	m_connections = {
		m_menuView->DoOnCommand(std::bind_front(&Messenger::OnCommand, this)),
		m_postService->DoOnNewMessage(std::bind_front(&Messenger::OnNewMessage, this)),
	};
}

void Messenger::Start()
{
	while (m_menuView)
	{
		std::osyncstream(m_output) << "you> ";
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
	case ui::MenuCommand::Message:
		m_postService->SendMesssage(app::MessageData{ "first", params.GetData() });
		break;
	default:
		m_chatView->ShowMessage(params.GetCommand());
		break;
	}
}

void Messenger::OnNewMessage(app::MessageData&& message)
{
	m_chatView->ShowMessage(std::move(message));
}
} // namespace client