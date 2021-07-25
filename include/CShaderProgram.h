#pragma once
#include <string>
#include "glad.h"
#include <glm/mat3x3.hpp>
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

namespace rbe {

    enum class EShaderType : GLenum
    {
        Vertex   = GL_VERTEX_SHADER,
        Fragment = GL_FRAGMENT_SHADER
    };

    template <typename OStream> OStream& operator<<(OStream& os, EShaderType t);

    class CShader {
        std::string m_sFileName;
        GLuint      m_iShaderId;
        EShaderType m_iShaderType;
    public:
        CShader(const char* fileName, EShaderType shaderType);

        GLuint GetId() const { return m_iShaderId; };

        EShaderType GetType() const { return m_iShaderType; };

        ~CShader();
    };

    class CShaderProgram {
        GLuint m_iProgramId{ 0 };
        GLint m_iUniformWorldLoc{ 0 };
        GLint m_iUniformModelLoc{ 0 };
        GLint m_iAttribPositionLoc{ 0 };
    public:
        CShaderProgram(const CShader& vertex, const CShader& fragment);
        CShaderProgram(CShaderProgram&& other) noexcept;
        GLint GetUniformLocation(const char* name);
        GLint GetAttribLocation(const char* name);
        GLuint GetId() const;
        void SetModel(const glm::mat3& modelMat);
        void SetWorld(const glm::mat3& worldMat);
        void SetPosition(const glm::vec2& posVec);
        void Use();
        ~CShaderProgram();
    private:
        int GetLocations();
    };

    using CShaderProgramPtr = std::shared_ptr<CShaderProgram>;

}
