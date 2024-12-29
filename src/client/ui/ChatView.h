#pragma once
#include "IChatView.h"

namespace client::ui
{
class ChatView : public IChatView
{
public:
	ChatView();

	void Draw() const override;

	void SetChat() override;
};
} // namespace client::ui