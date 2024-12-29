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
}

void Messenger::Start()
{
	std::cout << "Messenger started" << std::endl;
	m_menuView->Start();
}
} // namespace client