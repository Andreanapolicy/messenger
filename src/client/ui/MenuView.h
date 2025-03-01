#pragma once
#include "IMenuView.h"

namespace client::ui
{

class MenuView final : public IMenuView
{
public:
	MenuView(std::ostream& output);

	void Draw() const;
	void HandleCommand() override;

	Connection DoOnCommand(const MenuCommandSlot& handler) override;

private:
	using Handler = std::function<void(const std::string& data)>;
	using ActionMap = std::unordered_map<std::string, Handler>;

	std::ostream& m_output;
	const ActionMap m_actionMap;
	MenuCommandSignal m_onCommand;
	bool m_inChat = false;
};
} // namespace client::ui