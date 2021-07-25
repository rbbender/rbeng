#include <spdlog/spdlog.h>
#include "CGLVertexArray.h"

namespace rbe
{
    CGLVertexArray::CGLVertexArray()
    {
        GLuint vaid{ 0 };
        glGenVertexArrays(1, &vaid);
        if (0 == vaid)
        {
            spdlog::error("CGLVertexArray: error creating glVertexArray");
            throw std::runtime_error{ "CGLVertexArray: error creating glVertexArray" };
        }
        SetGLId(vaid);
        spdlog::trace("CGLVertexArray: +#{} @{}", GetGLId(), (void*) this);
    }

    CGLVertexArray::~CGLVertexArray()
    {
        auto vaid = GetGLId();
        if (0 == vaid)
            return;
        glDeleteVertexArrays(1, &vaid);
        SetGLId(0);
        spdlog::trace("CGLVertexArray: -#{} @{}", vaid, (void*) this);
    }

    void CGLVertexArray::Bind()
    {
        glBindVertexArray(GetGLId());
    }

    void CGLVertexArray::Unbind()
    {
        glBindVertexArray(0);
    }
}
