#pragma once

namespace client::ui
{
class IDrawable
{
public:
	virtual ~IDrawable() = default;

	virtual void Draw() const = 0;
};
} // namespace client::ui