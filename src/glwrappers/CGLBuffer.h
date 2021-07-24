#pragma once

#include "CGLBaseObject.h"

namespace rbe
{
    class CGLBuffer : public CGLBaseObject
    {
        GLenum m_iBindTarget{ 0 };
    public:
        CGLBuffer();
        ~CGLBuffer();
        void Bind(GLenum target);
        void Unbind();
        GLenum GetBoundTarget() const { return m_iBindTarget; };
    };
}
