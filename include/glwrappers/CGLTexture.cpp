#include <spdlog/spdlog.h>
#include "CGLTexture.h"

namespace rbe
{
    CGLTexture::CGLTexture()
    {
        GLuint textureid{ 0 };
        glGenTextures(1, &textureid);
        if (0 == textureid)
        {
            spdlog::error("CGLTexture: error creating new glTexture");
            throw std::runtime_error{ "CGLTexture: error creating new glTexture" };
        }
        SetGLId(textureid);
        spdlog::trace("CGLTexture: +#{} @{}", GetGLId(), (void*) this);
    }

    CGLTexture::CGLTexture(GLuint id)
    {
        SetGLId(id);
        spdlog::trace("CGLTexture: +#{} set @{}", GetGLId(), (void*) this);
    }

    CGLTexture::~CGLTexture()
    {
        auto textureid = GetGLId();
        if (0 == textureid)
            return;
        glDeleteTextures(1, &textureid);
        spdlog::trace("CGLTexture: -#{} @{}", textureid, (void*) this);
        SetGLId(0);
    }

    void CGLTexture::Bind(GLenum target)
    {
        //if (0 != m_iBindTarget)
        //{
        //    spdlog::warn("CGLTexture: #{} @{}: binding to {} while was already bound to {}",
        //        GetGLId(), (void*) this, target, m_iBindTarget);
        //}
        glBindTexture(target, GetGLId());
        m_iBindTarget = target;
    }

    void CGLTexture::Unbind()
    {
        glBindTexture(m_iBindTarget, 0);
        m_iBindTarget = 0;
    }


}