#pragma once
#include "IMenuView.h"

namespace client::ui
{

class MenuView : public IMenuView
{
public:
	MenuView();

	void Draw() const override;
	void Start() override;

	Connection DoOnCommand(const MenuCommandSlot& handler) override;

private:
	MenuCommandSignal m_onCommand;
};
} // namespace client::ui