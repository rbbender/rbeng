#pragma once

#include "CGLBaseObject.h"

namespace rbe
{
    class CGLTexture : public CGLBaseObject
    {
        GLenum m_iBindTarget{ 0 };
    public:
        CGLTexture();
        CGLTexture(GLuint id);
        ~CGLTexture();
        void Bind(GLenum target);
        void Unbind();
        GLenum GetBoundTarget() const { return m_iBindTarget; };
    };
}
