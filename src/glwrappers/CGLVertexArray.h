#pragma once

#include "CGLBaseObject.h"

namespace rbe
{
    class CGLVertexArray : public CGLBaseObject
    {
    public:
        CGLVertexArray();
        ~CGLVertexArray();
        void Bind();
        void Unbind();
    };
}
