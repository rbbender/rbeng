#pragma once
#include "glwrappers/CGLTexture.h"
#include <memory>

namespace rbe {
    class CTexture {
        CGLTexture m_gltexture;
        int m_szWidth;
        int m_szHeight;
        int m_iNChannels;
    public:
        CTexture();
        CTexture(GLuint);
        CTexture(const char* fileName);

        int GetWidth() const;
        int GetHeight() const;

        void SetWidth(int w);
        void SetHeight(int h);
        void Use();

        GLuint GetId() const;

    };

	using CTexturePtr = std::shared_ptr<CTexture>;
}


