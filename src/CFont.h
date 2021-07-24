#pragma once

#include <string>
#include <map>
#include <glm/vec2.hpp>
#include "CTexture.h"

namespace rbe {
    void InitFonts();
    void ReleaseFonts();

    struct CChar {
        CTexturePtr texture;
        glm::ivec2  size;
        glm::ivec2  bearing;
        unsigned    advance;
    };

    using CCharPtr = std::shared_ptr<CChar>;

    class CFont {
        std::string m_sFontPath;
        int         m_iFontSize;
        std::map<int, CCharPtr> m_vcChars;
    public:
        CFont(const char* fontFilePath, int fontHeight = 32);
        void LoadSize(int fontHeight);
        CCharPtr GetChar(int code);
    };

    using CFontPtr = std::shared_ptr<CFont>;
}
