#include "rbe.h"
#include "CShaderProgram.h"
#include "CFont.h"

namespace rbe
{
	static void glfw_error_cb(int error, const char* description) {
		spdlog::error("GLFW error: {} {}", description, error);
	}

	RBE_RESULT InitGLFW()
	{
		glfwSetErrorCallback(glfw_error_cb);
		if (!glfwInit())
		{
			spdlog::error("Unable to initialize GLFW");
			return RBE_RESULT::FAILURE;
		}
		return RBE_RESULT::SUCCESS;
	}

	RBE_RESULT AddWindowToLoop(CBasicWindowPtr p)
	{
		AddWindow(p);
		return RBE_RESULT::SUCCESS;
	}
	
	RBE_RESULT Loop()
	{
		auto& windows = GetWindows();
		while (windows.size())
		{
			glfwPollEvents();
			for (auto wnd : windows)
			{
				wnd->Draw();
				if (wnd->IsShouldClose())
				{
					RemoveWindow(wnd);
				}
			}
		}
		return RBE_RESULT::SUCCESS;
	}
}
