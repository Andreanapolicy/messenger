// clang-format off
#include "../pch.h"
// clang-format on
#include "ChatView.h"

namespace client::ui
{

ChatView::ChatView(std::ostream& output)
	: m_output{ output }
{
}

void ChatView::ShowMessage(app::MessageData&& message)
{
	std::osyncstream(m_output) << std::endl
							   << message.from << "> " << message.data << std::endl
							   << "you> ";
}

void ChatView::ShowMessage(MenuCommand command)
{
	switch (command)
	{
	case ui::MenuCommand::ShowChats:
		m_output << "!> show-chats now is not available" << std::endl;
		break;
	case ui::MenuCommand::OpenChat:
		m_output << "!> you opened chat" << std::endl;
		break;
	case ui::MenuCommand::Unknown:
	default:
		m_output << "!> now a command. Use <:help>" << std::endl;
		break;
	}
}

} // namespace client::ui