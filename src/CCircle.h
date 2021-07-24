#pragma once

#include <glm/vec3.hpp>
#include <glm/mat3x3.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "CDrawable.h"
#include "glwrappers/glwrappers.h"

namespace rbe
{
    class CCircle : public CDrawable
    {
        static constexpr int       CNT_POINTS{ 120 };
        CGLVertexArray  m_vao;
        CGLBuffer       m_vbPoints;
        int             m_iRadius{ 10 };
        glm::vec3       m_v3Color{ 1.0f };
        glm::mat3       m_m3Model{ 1.0f };
        GLint           m_gliColor{ -1 };
    public:
        CCircle();
        CCircle(int radius, const glm::vec3& color);
        void SetRadius(int radius) {
            m_iRadius = radius;
        };
        int GetRadius() const {
            return m_iRadius;
        };
        void SetColor(const glm::vec3& color) { m_v3Color = color; };
        glm::vec3 GetColor() const { return m_v3Color; };

        void Draw(int x, int y) override;

    private:
        void RecalculatePoints();
    };
}
