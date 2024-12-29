#pragma once
#include "../../common/signals/Signals.h"
#include "IDrawable.h"

namespace client::ui
{

enum class MenuCommand
{
	ShowChats, // show all available chats
	OpenChat, // open selected chat
	Exit, // exit from app
};

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

class IMenuView : public IDrawable
{
public:
	using MenuCommandSignal = boost::signals2::signal<void(MenuCommandParams)>;
	using MenuCommandSlot = MenuCommandSignal::slot_type;

	virtual ~IMenuView() = default;

    virtual void Start() = 0;

	virtual Connection DoOnCommand(const MenuCommandSlot& handler) = 0;
};
} // namespace client::ui