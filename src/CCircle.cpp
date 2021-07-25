
#include <cmath>
#include <array>
#include <common.h>
#include <CCircle.h>

namespace rbe
{
    CCircle::CCircle()
        : CCircle{10, glm::vec3(1.0f, 1.0f, 1.0f)}
    {}

    CCircle::CCircle(int radius, const glm::vec3& color)
        : m_iRadius{radius},
        m_v3Color{color}
    {
        auto shader = GetDefaultPrimitiveShader();
        m_gliColor = shader->GetUniformLocation("color");
        m_vao.Bind();
        m_vbPoints.Bind(GL_ARRAY_BUFFER);
        glBufferData(m_vbPoints.GetBoundTarget(), sizeof(float)* CNT_POINTS * 2, nullptr, GL_DYNAMIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
        m_vao.Unbind();
        m_vbPoints.Unbind();
        RecalculatePoints();
    }

    void CCircle::Draw(int x, int y)
    {
        m_m3Model[2][0] = x;
        m_m3Model[2][1] = -y; // Y axis is reversed
        auto shader = GetDefaultPrimitiveShader();
        shader->Use();
        shader->SetModel(m_m3Model);
        glUniform3fv(m_gliColor, 1, glm::value_ptr(m_v3Color));
        m_vao.Bind();
        m_vbPoints.Bind(GL_ARRAY_BUFFER);
        glDrawArrays(GL_LINE_LOOP, 0, CNT_POINTS);
        m_vbPoints.Unbind();
        m_vao.Unbind();
    }

    void CCircle::RecalculatePoints()
    {
        std::array<float, CNT_POINTS * 2> points;
        float angle = 0.0f; // initial angle
        const float angle_inc = 2 * 3.1415f / CNT_POINTS; // circumference into defined number of points, radians

        for (int i = 0; i < CNT_POINTS; ++i)
        {
            points[static_cast<size_t>(i) * 2]     = static_cast<int>(m_iRadius * cosf(angle));
            points[static_cast<size_t>(i) * 2 + 1] = static_cast<int>(m_iRadius * sinf(angle));
            angle += angle_inc;
        }
        m_vbPoints.Bind(GL_ARRAY_BUFFER);
        glBufferSubData(m_vbPoints.GetBoundTarget(), 0, sizeof(float) * CNT_POINTS * 2, points.data());
        m_vbPoints.Unbind();
    }
}