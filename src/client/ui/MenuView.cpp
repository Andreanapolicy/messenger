#include "../pch.h"
#include "MenuView.h"
#include <iostream>

namespace client::ui
{

MenuView::MenuView()
{
}

void MenuView::Draw() const
{

}

void MenuView::Start()
{
    std::cout << "Menu" << std::endl;
}

Connection MenuView::DoOnCommand(const MenuCommandSlot& handler)
{
	return m_onCommand.connect(handler);
}
} // namespace client::ui