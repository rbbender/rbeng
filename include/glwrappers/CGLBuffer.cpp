#include <spdlog/spdlog.h>
#include "CGLBuffer.h"

namespace rbe
{
    CGLBuffer::CGLBuffer()
    {
        GLuint bufferid{ 0 };
        glGenBuffers(1, &bufferid);
        if (0 == bufferid)
        {
            spdlog::error("CGLBuffer: error creating glBuffer");
            throw std::runtime_error{ "CGLBuffer: error creating glBuffer" };
        }
        SetGLId(bufferid);
        spdlog::trace("CGLBuffer: +#{} @{}", GetGLId(), (void*) this);
    }

    CGLBuffer::~CGLBuffer()
    {
        auto bufferid = GetGLId();
        if (0 == bufferid)
        {
            return;
        }
        glDeleteBuffers(1, &bufferid);
        SetGLId(0);
        spdlog::trace("CGLBuffer: -#{} @{}", bufferid, (void*) this);
    }

    void CGLBuffer::Bind(GLenum target)
    {
        //if (0 != m_iBindTarget)
        //{
        //    spdlog::warn("CGLBuffer: #{} @{}: binding to {} while was already bound to {}",
        //        GetGLId(), (void*) this, target, m_iBindTarget);
        //}
        glBindBuffer(target, GetGLId());
        m_iBindTarget = target;
    }

    void CGLBuffer::Unbind()
    {
        glBindBuffer(m_iBindTarget, 0);
        m_iBindTarget = 0;
    }

}