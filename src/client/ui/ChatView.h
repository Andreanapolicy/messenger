#pragma once
#include "IChatView.h"

namespace client::ui
{
class ChatView final : public IChatView
{
public:
	ChatView(std::ostream& output);

	void ShowMessage(app::MessageData&& message) override;
	void ShowMessage(MenuCommand command) override;

private:
	std::ostream& m_output;
};
} // namespace client::ui