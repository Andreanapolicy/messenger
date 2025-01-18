#pragma once
#include "../../common/signals/Signals.h"
#include "MenuCommand.h"

namespace client::ui
{

struct MenuCommandParams
{
public:
	MenuCommandParams(MenuCommand command, const std::string& data)
		: m_data{ data }
		, m_command{ command }
	{
	}

	std::string GetData() const { return m_data; }
	MenuCommand GetCommand() const { return m_command; }

private:
	std::string m_data;
	MenuCommand m_command;
};

class IMenuView
{
public:
	using MenuCommandSignal = boost::signals2::signal<void(MenuCommandParams)>;
	using MenuCommandSlot = MenuCommandSignal::slot_type;

	virtual ~IMenuView() = default;

	virtual void HandleCommand() = 0;

	virtual Connection DoOnCommand(const MenuCommandSlot& handler) = 0;
};
} // namespace client::ui