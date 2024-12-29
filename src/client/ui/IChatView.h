#pragma once
#include "IDrawable.h"

namespace client::ui
{
class IChatView : public IDrawable
{
public:
	virtual ~IChatView() = default;

	virtual void SetChat() = 0;
};
} // namespace client::ui