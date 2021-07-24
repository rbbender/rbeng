#pragma once
#include <string>
#include <glm/vec3.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "glwrappers/glwrappers.h"
#include "CDrawable.h"
#include "CShaderProgram.h"
#include "CFont.h"

namespace rbe {
    class CText : public CDrawable
    {
        CGLVertexArray m_vao;
        CGLBuffer m_vbo;
        GLint   m_iTextColLoc{ 0 };
        std::string m_sText{ "" };
        glm::vec3   m_v3Color{ 1.0f, 1.0f, 1.0f };
        CFontPtr    m_pFont;
        CShaderProgramPtr   m_pShader;
    public:
        CText();
        CText(const std::string& s);
        CText(CFontPtr font);
        CText(CFontPtr font, CShaderProgramPtr shader);
        CText(const std::string& s, CFontPtr font, CShaderProgramPtr shader);
        CText(const std::string& s, CFontPtr font);
        void Draw(int x, int y) override;
        void SetText(const char* ps);
        void SetText(const std::string& s);
        void SetColor(const glm::vec3& c);
        void SetColor(float r, float g, float b);
        void SetFont(CFontPtr pf);
        void SetShader(CShaderProgramPtr sh);

        CFontPtr GetFont() const;
        CShaderProgramPtr GetShader() const;
    private:
        void InitGL();
        void SetTextColorUniform();
        void UpdateTextColorLoc();
    };

    using CTextPtr = std::shared_ptr<CText>;
}