#include "MenuView.h"
#include "../pch.h"
#include <iostream>
#include <sstream>

namespace client::ui
{

MenuView::MenuView()
	: m_actionMap({ { ":show-chats", [this](const std::string& data) { m_onCommand(MenuCommandParams{ MenuCommand::ShowChats, data }); m_inChat = true; } },
		{ ":oc", [this](const std::string& data) { m_onCommand(MenuCommandParams{ MenuCommand::OpenChat, data }); m_inChat = true; } },
		{ ":exit", [this](const std::string&) { m_onCommand(MenuCommandParams{ MenuCommand::Exit, "" }); m_inChat = true; } },
		{ ":help", [this](const std::string&) { Draw(); } } })
{
}

void MenuView::Draw() const
{
	std::cout << ":show-chats - turn on engine" << std::endl;
	std::cout << ":open-chat - turn off engine" << std::endl;
	std::cout << ":exit <number> - set speed" << std::endl;
	std::cout << ":help <number> - set gear" << std::endl;
}

void MenuView::HandleCommand()
{
	std::string commandLine;
	std::getline(std::cin, commandLine);

	std::istringstream stream(commandLine);

	std::string action;
	std::string data;
	std::getline(stream, action, ' ');
	stream >> data;

	auto it = m_actionMap.find(action);
	if (it != m_actionMap.end())
	{
		it->second(data);
	}
	else if (m_inChat)
	{
		m_onCommand(MenuCommandParams{ MenuCommand::Message, commandLine });
	}
	else
	{
		m_onCommand(MenuCommandParams{ MenuCommand::Unknown, "" });
	}
}

Connection MenuView::DoOnCommand(const MenuCommandSlot& handler)
{
	return m_onCommand.connect(handler);
}
} // namespace client::ui