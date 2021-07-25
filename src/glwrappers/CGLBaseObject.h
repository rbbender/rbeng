#pragma once

#include "glad.h"

namespace rbe {
    class CGLBaseObject
    {
        GLuint m_uiGlId{ 0 };
    public:
        void SetGLId(GLuint id) { m_uiGlId = id; };
        GLuint GetGLId() const { return m_uiGlId; };
        virtual ~CGLBaseObject() {};
    };
}
