#pragma once
#include "../app/MessageData.h"
#include "MenuCommand.h"

namespace client::ui
{
class IChatView
{
public:
	virtual ~IChatView() = default;

	virtual void ShowMessage(app::MessageData&& message) = 0;

	virtual void ShowMessage(MenuCommand command) = 0;
};
} // namespace client::ui