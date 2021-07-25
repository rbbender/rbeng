#include <array>
#include <spdlog/spdlog.h>
#include <ft2build.h>
#include FT_FREETYPE_H
#include <CFont.h>

namespace rbe {

    FT_Library  fontLib;

    void InitFonts()
    {
        if (FT_Init_FreeType(&fontLib))
        {
            spdlog::error("Fonts: unable to initialize FreeType");
            throw std::runtime_error{ "Unable to initialize FreeType" };
        }
    }

    void ReleaseFonts()
    {
        FT_Done_FreeType(fontLib);
    }

    CFont::CFont(const char* fontFilePath, int fontHeight)
        : m_sFontPath{ fontFilePath },
        m_iFontSize{ fontHeight }
    {
        LoadSize(m_iFontSize);
    }

    void CFont::LoadSize(int fontHeight)
    {
        FT_Face fontFace;
        if (FT_New_Face(fontLib, m_sFontPath.c_str(), 0, &fontFace))
        {
            spdlog::error("Fonts: unable to load font face {}", m_sFontPath);
            throw std::runtime_error{ "Unable to load font" };
        }

        FT_Set_Pixel_Sizes(fontFace, 0, fontHeight);

        m_vcChars.empty();

        std::array<CTexturePtr, 128> font_textures;

        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        for (int i = 0; i < 128; ++i)
        {
            if (FT_Load_Char(fontFace, i, FT_LOAD_RENDER))
            {
                spdlog::error("Error loading char glyph: {}", i);
                throw std::runtime_error{ "Error loading char glyph" };
            }
            auto t = font_textures[i] = std::make_shared<CTexture>();
            t->Use();
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, fontFace->glyph->bitmap.width, fontFace->glyph->bitmap.rows,
                0, GL_RED, GL_UNSIGNED_BYTE, fontFace->glyph->bitmap.buffer);

            t->SetWidth(fontFace->glyph->bitmap.width);
            t->SetHeight(fontFace->glyph->bitmap.rows);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            auto c = std::make_shared<CChar>();
            c->texture = t;
            c->size = glm::ivec2{ t->GetWidth(), t->GetHeight() };
            c->bearing = glm::ivec2{ fontFace->glyph->bitmap_left, fontFace->glyph->bitmap_top };
            c->advance = static_cast<unsigned int>(fontFace->glyph->advance.x);

            m_vcChars.emplace(std::make_pair(i, c));
        }
        FT_Done_Face(fontFace);
    }

    CCharPtr CFont::GetChar(int code)
    {
        auto c = m_vcChars.find(code);
        if (c == m_vcChars.end())
        {
            return nullptr;
        }
        return c->second;
    }

}
