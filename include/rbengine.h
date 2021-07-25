#pragma once

#include "CWindow2D.h"
#include "CTexture.h"
#include "CText.h"
#include "CDecal.h"
#include "CCircle.h"
#include "CShaderProgram.h"
#include "CFont.h"
#include "common.h"

namespace rbe
{
	RBE_RESULT InitGLFW();
	RBE_RESULT AddWindowToLoop(CBasicWindowPtr p);
	RBE_RESULT Loop();
}
