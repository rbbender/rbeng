#include <CDecal.h>
#include <common.h>

namespace rbe {
    CDecal::CDecal(CTexturePtr pTexture) :
        CDecal(pTexture, GetDefaultShader())
    {
    }
    CDecal::CDecal(CTexturePtr pTexture, CShaderProgramPtr pProgram) :
        m_pTexture{ pTexture },
        m_pProgram{ pProgram }
    {
        int tWidth = m_pTexture->GetWidth();
        int tHeight = m_pTexture->GetHeight();
        std::vector<float> objCoords{ -1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 1.0f,   1.0f, 1.0f, 1.0f, -1.0f, -1.0f, -1.0f };
        std::vector<float> texCoords{ 0.0f,0.0f, 0.0f,1.0f, 1.0f,1.0f,  1.0f,1.0f, 1.0f,0.0f, 0.0f,0.0f };
        m_vao.Bind();
        m_vbObj.Bind(GL_ARRAY_BUFFER);
        glBufferData(m_vbObj.GetBoundTarget(), objCoords.size() * sizeof(float), objCoords.data(), GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
        m_vbObj.Unbind();
        m_vbTex.Bind(GL_ARRAY_BUFFER);
        glBufferData(m_vbTex.GetBoundTarget(), texCoords.size() * sizeof(float), texCoords.data(), GL_STATIC_DRAW);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
        m_vbTex.Unbind();
        m_vao.Unbind();
        RecalculateModel();
    }

    void CDecal::Scale(float sx, float sy) {
        m_fScaleX = sx;
        m_fScaleY = sy;
        spdlog::debug("Object scale = {}", sx);
        RecalculateModel();
    }

    void CDecal::ScaleX(float sx) {
        m_fScaleX = sx;
        RecalculateModel();
    }

    void CDecal::ScaleY(float sy) {
        m_fScaleY = sy;
        RecalculateModel();
    }

    void CDecal::Draw(int x, int y) {
        m_pProgram->Use();
        m_pTexture->Use();
        glm::mat3 objMat = m_matModel;
        objMat[2][0] += static_cast<float>(x);
        objMat[2][1] -= static_cast<float>(y);
        m_pProgram->SetModel(objMat);
        m_vao.Bind();
        glDrawArrays(GL_TRIANGLES, 0, 6);
        m_vao.Unbind();
    }

    int CDecal::GetScaledSizeX() const
    {
        return static_cast<int>(m_fScaleX * m_pTexture->GetWidth());
    }

    int CDecal::GetScaledSizeY() const
    {
        return static_cast<int>(m_fScaleY * m_pTexture->GetHeight());
    }

    void CDecal::RecalculateModel() {
        m_matModel[0][0] = m_pTexture->GetWidth() * m_fScaleX;
        m_matModel[1][1] = m_pTexture->GetHeight() * m_fScaleY;
        m_matModel[2][0] = m_pTexture->GetWidth() * 1.0f * m_fScaleX;
        m_matModel[2][1] = m_pTexture->GetHeight() * -1.0f * m_fScaleY;

        m_pProgram->SetModel(m_matModel);
    }
}
