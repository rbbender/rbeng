#include <vector>
#include <common.h>
#include <spdlog/spdlog.h>

namespace rbe
{
	static CShaderProgramPtr _defaultShader = nullptr;
	static CShaderProgramPtr _defaultTextShader = nullptr;
	static CShaderProgramPtr _defaultPrimitiveShader = nullptr;
	static CFontPtr			 _defaultFont = nullptr;
	static std::vector<CBasicWindowPtr> _windows;

	int SetDefaultShader(CShaderProgramPtr pShader)
	{
		_defaultShader = pShader;
		return 0;
	}
	int SetDefaultTextShader(CShaderProgramPtr pShader)
	{
		_defaultTextShader = pShader;
		return 0;
	}
	int SetDefaultPrimitiveShader(CShaderProgramPtr pShader)
	{
		_defaultPrimitiveShader = pShader;
		return 0;
	}
	CShaderProgramPtr GetDefaultShader()
	{
		return _defaultShader;
	}
	CShaderProgramPtr GetDefaultTextShader()
	{
		return _defaultTextShader;
	}

	CShaderProgramPtr GetDefaultPrimitiveShader()
	{
		return _defaultPrimitiveShader;
	}

	int SetDefaultFont(CFontPtr pFont)
	{
		_defaultFont = pFont;
		return 0;
	}

	CFontPtr GetDefaultFont()
	{
		return _defaultFont;
	}

	void AddWindow(CBasicWindowPtr wnd)
	{
		if (std::find_if(_windows.begin(), _windows.end(), [&wnd](auto el) {return wnd.get() == el.get(); }) == _windows.end())
		{
			_windows.push_back(wnd);
		}
	}

	void RemoveWindow(CBasicWindowPtr wnd)
	{

		auto el = std::find_if(_windows.begin(), _windows.end(), [&wnd](auto el) {return wnd.get() == el.get(); });
		if (el != _windows.end())
		{
			_windows.erase(el);
		}
	}

	std::vector<CBasicWindowPtr>& GetWindows()
	{
		return _windows;
	}
}
