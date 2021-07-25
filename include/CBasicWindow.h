#pragma once
#include <memory>

namespace rbe
{
	class CBasicWindow
	{
	public:
		virtual void ProcessKey(int key, int scancode, int action, int mods) = 0;
		virtual void Resize(int w, int h) = 0;
		virtual int GetWidth() const = 0;
		virtual int GetHeight() const = 0;
		virtual void Draw() = 0;
		virtual bool IsShouldClose() = 0;
		virtual ~CBasicWindow() {};
	};

	using CBasicWindowPtr = std::shared_ptr<CBasicWindow>;
}
