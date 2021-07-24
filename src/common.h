#pragma once

#include <vector>
#include "CShaderProgram.h"
#include "CBasicWindow.h"
#include "CFont.h"

namespace rbe
{
	enum class RBE_RESULT
	{
		SUCCESS,
		FAILURE
	};

	int SetDefaultShader(CShaderProgramPtr pShader);
	int SetDefaultTextShader(CShaderProgramPtr pShader);
	int SetDefaultPrimitiveShader(CShaderProgramPtr pShader);
	CShaderProgramPtr GetDefaultShader();
	CShaderProgramPtr GetDefaultTextShader();
	CShaderProgramPtr GetDefaultPrimitiveShader();
	int SetDefaultFont(CFontPtr pFont);
	CFontPtr GetDefaultFont();
	void AddWindow(CBasicWindowPtr);
	void RemoveWindow(CBasicWindowPtr);
	std::vector<CBasicWindowPtr>& GetWindows();
}
