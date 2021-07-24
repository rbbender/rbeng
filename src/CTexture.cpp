#include "CTexture.h"
#include <spdlog/spdlog.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <stdexcept>

namespace rbe {

    CTexture::CTexture() :
        m_szWidth{ 0 },
        m_szHeight{ 0 },
        m_iNChannels{ 0 }
    {
        spdlog::debug("+CTexture @{} #{}", (void*)this, m_gltexture.GetGLId());
    }

    CTexture::CTexture(GLuint id)
        : m_szWidth{ 0 },
        m_szHeight{ 0 },
        m_iNChannels{ 0 },
        m_gltexture{ id }
    {
        spdlog::debug("+CTexture @{} set #{}", (void*)this, m_gltexture.GetGLId());
    }

    CTexture::CTexture(const char* fileName) :
        CTexture()
    {
        unsigned char* data = stbi_load(fileName, &m_szWidth, &m_szHeight, &m_iNChannels, 0);
        if (!data) {
            throw std::runtime_error{ "Unable to load file" };
        }
        m_gltexture.Bind(GL_TEXTURE_2D);
        glTexImage2D(m_gltexture.GetBoundTarget(), 0, GL_RGBA, m_szWidth, m_szHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(m_gltexture.GetBoundTarget());
        m_gltexture.Unbind();
        stbi_image_free(data);
        spdlog::debug("Texture @{} #{} loaded from file {} w: {} h: {} channels: {}",
            (void*)this, m_gltexture.GetGLId(), fileName, m_szWidth, m_szHeight, m_iNChannels);
    }

    GLuint CTexture::GetId() const
    {
        return m_gltexture.GetGLId();
    }

    int CTexture::GetWidth() const
    {
        return m_szWidth;
    }

    int CTexture::GetHeight() const
    {
        return m_szHeight;
    }

    void CTexture::SetWidth(int w)
    {
        m_szWidth = w;
    }

    void CTexture::SetHeight(int h)
    {
        m_szHeight = h;
    }

    void CTexture::Use()
    {
        m_gltexture.Bind(GL_TEXTURE_2D);
    }


}
