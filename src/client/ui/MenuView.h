#pragma once
#include "IMenuView.h"

namespace client::ui
{

class MenuView : public IMenuView
{
public:
	MenuView();

	void Draw() const override;
	void HandleCommand() override;

	Connection DoOnCommand(const MenuCommandSlot& handler) override;

private:
	using Handler = std::function<void(const std::string& data)>;
	using ActionMap = std::map<std::string, Handler>;

	const ActionMap m_actionMap;
	MenuCommandSignal m_onCommand;
};
} // namespace client::ui