#pragma once
#include "glwrappers/glwrappers.h"
#include "CDrawable.h"
#include "CTexture.h"
#include "CShaderProgram.h"

namespace rbe {
    class CDecal : public CDrawable {
        CTexturePtr m_pTexture;
        CShaderProgramPtr m_pProgram;
        CGLVertexArray m_vao;
        CGLBuffer m_vbObj;
        CGLBuffer m_vbTex;
        float m_fScaleX{ 1.0f };
        float m_fScaleY{ 1.0f };

        // Internal matrices
        glm::mat3 m_matModel{ 1.0f };
    public:
        CDecal(CTexturePtr pTexture);
        CDecal(CTexturePtr pTexture, CShaderProgramPtr pProgram);
        void Scale(float sx, float sy);
        void ScaleX(float sx);
        void ScaleY(float sy);
        int GetScaledSizeX() const;
        int GetScaledSizeY() const;
        void Draw(int x, int y) override;

    private:
        void RecalculateModel();
    };

	using CDecalPtr = std::shared_ptr<CDecal>;
}



