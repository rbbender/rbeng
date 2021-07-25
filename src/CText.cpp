#include <CText.h>
#include <common.h>

namespace rbe {
    CText::CText() :
        CText{GetDefaultFont(), GetDefaultTextShader()}
    {
    }
    CText::CText(const std::string& s) :
        CText{s, GetDefaultFont(), GetDefaultTextShader()}
    {
    }
    CText::CText(CFontPtr font) :
        CText(font, GetDefaultTextShader())
    {
    }
    CText::CText(CFontPtr font, CShaderProgramPtr shader)
        : m_v3Color{ 1.0f, 1.0f, 1.0f },
        m_pFont{ font },
        m_pShader{ shader }
    {
        InitGL();
        UpdateTextColorLoc();
    }

    CText::CText(const std::string& s, CFontPtr font, CShaderProgramPtr shader)
        : m_sText{ s },
        m_v3Color{ 1.0f, 1.0f, 1.0f },
        m_pFont{ font },
        m_pShader{ shader }
    {
        InitGL();
        UpdateTextColorLoc();
    }

    CText::CText(const std::string& s, CFontPtr font) :
        CText(s, font, GetDefaultTextShader())
    {
    }

    void CText::Draw(int x, int y)
    {
        // copied from learnopengl
        m_pShader->Use();
        m_vao.Bind();

        for (auto c : m_sText)
        {
            auto ch = m_pFont->GetChar(c);
            float xpos = x + ch->bearing.x;
            float ypos = y - (ch->size.y - ch->bearing.y);
            float w = ch->size.x;
            float h = ch->size.y;
            float vertices[6][4] = {
                {xpos,          ypos + h,       0.0f,   0.0f},
                {xpos,          ypos,           0.0f,   1.0f},
                {xpos + w,      ypos,           1.0f,   1.0f},

                {xpos,          ypos + h,       0.0f,   0.0f},
                {xpos + w,      ypos,           1.0f,   1.0f},
                {xpos + w,      ypos + h,       1.0f,   0.0f}
            };
            ch->texture->Use();
            m_vbo.Bind(GL_ARRAY_BUFFER);
            glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
            glDrawArrays(GL_TRIANGLES, 0, 6);
            x += (static_cast<int>(ch->advance) >> 6);
        }
        m_vao.Unbind();
    }

    void CText::SetText(const char* ps)
    {
        m_sText = ps;
    }

    void CText::SetText(const std::string& rs)
    {
        m_sText = rs;
    }

    void CText::SetColor(const glm::vec3& rc)
    {
        m_v3Color = rc;
        SetTextColorUniform();
    }

    void CText::SetColor(float r, float g, float b)
    {
        m_v3Color.r = r;
        m_v3Color.g = g;
        m_v3Color.b = b;
        SetTextColorUniform();
    }

    void CText::SetFont(CFontPtr pf)
    {
        if (!pf)
        {
            throw std::runtime_error{ "CText: empty font" };
        }
        m_pFont = pf;
    }

    void CText::SetShader(CShaderProgramPtr sh)
    {
        if (!sh)
        {
            throw std::runtime_error{ "CText: empty shader" };
        }
        m_pShader = sh;
        UpdateTextColorLoc();
    }

    CFontPtr CText::GetFont() const
    {
        return m_pFont;
    }

    CShaderProgramPtr CText::GetShader() const
    {
        return m_pShader;
    }

    void CText::InitGL()
    {
        m_vao.Bind();
        m_vbo.Bind(GL_ARRAY_BUFFER);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, nullptr, GL_DYNAMIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);
        m_vbo.Unbind();
        m_vao.Unbind();
    }

    void CText::SetTextColorUniform()
    {
        m_pShader->Use();
        glUniform3fv(m_iTextColLoc, 1, glm::value_ptr(m_v3Color));
    }

    void CText::UpdateTextColorLoc()
    {
        m_pShader->Use();
        if (!(m_iTextColLoc = m_pShader->GetUniformLocation("textColor")))
        {
            throw std::runtime_error{ "Invalid text shader: no textColor uniform" };
        }
    }
}
