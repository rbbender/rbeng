#include <fstream>
#include <sstream>
#include <glm/gtc/type_ptr.hpp>
#include "CShaderProgram.h"

namespace rbe {

    template <typename OStream> OStream& operator<<(OStream& os, EShaderType t) {
        if (t == EShaderType::Vertex)
            return os << "vertex";
        return os << "fragment";
    }

    CShader::CShader(const char* fileName, EShaderType shaderType) :
        m_sFileName{ fileName },
        m_iShaderId{ 0 },
        m_iShaderType{ shaderType }
    {
        std::ifstream ifs{ fileName };
        std::stringstream ss;
        ss << ifs.rdbuf();
        ifs.close();
        m_iShaderId = glCreateShader(static_cast<GLenum>(shaderType));
        spdlog::debug("Created shader of type {} file: {} id: {}", m_iShaderType, m_sFileName, m_iShaderId);
        std::string shadersrc{ ss.str() };
        auto pSrc = shadersrc.c_str();
        glShaderSource(m_iShaderId, 1, &pSrc, nullptr);
        glCompileShader(m_iShaderId);

        int status{ 0 };
        char info[1024] = { 0 };
        glGetShaderiv(m_iShaderId, GL_COMPILE_STATUS, &status);

        if (!status) {
            glGetShaderInfoLog(m_iShaderId, 1024, NULL, info);
            spdlog::error("Error compiling shader from file {}: {}", fileName, info);
            throw std::runtime_error{ "Error compiling shader" };
        }
    }


    CShader::~CShader() {
        glDeleteShader(m_iShaderId);
        spdlog::debug("Deleted shader id {} type {}", m_iShaderId, m_iShaderType);
        m_iShaderId = 0;
    }

    CShaderProgram::CShaderProgram(const CShader& vertex, const CShader& fragment)
    {
        m_iProgramId = glCreateProgram();
        spdlog::debug("Created shader program id: {} shaders: {}, {}",
            m_iProgramId, vertex.GetId(), fragment.GetId());
        glAttachShader(m_iProgramId, vertex.GetId());
        glAttachShader(m_iProgramId, fragment.GetId());
        glLinkProgram(m_iProgramId);

        int status;
        char info[1024];
        glGetProgramiv(m_iProgramId, GL_LINK_STATUS, &status);
        if (!status) {
            glGetProgramInfoLog(m_iProgramId, 1024, nullptr, info);
            spdlog::error("Error linking program id {}: {}", m_iProgramId, info);
            throw std::runtime_error{ "Error linking program" };
        }
        GetLocations();
    }

    CShaderProgram::CShaderProgram(CShaderProgram&& other) noexcept :
        m_iProgramId{ other.m_iProgramId },
        m_iUniformWorldLoc{ other.m_iUniformWorldLoc },
        m_iUniformModelLoc{ other.m_iUniformModelLoc },
        m_iAttribPositionLoc{ other.m_iAttribPositionLoc }
    {
        other.m_iProgramId = 0;
        other.m_iUniformWorldLoc = 0;
        other.m_iUniformModelLoc = 0;
        other.m_iAttribPositionLoc = 0;
    }

    GLint CShaderProgram::GetUniformLocation(const char* name) {
        return glGetUniformLocation(GetId(), name);
    }

    GLint CShaderProgram::GetAttribLocation(const char* name) {
        return glGetAttribLocation(GetId(), name);
    }

    GLuint CShaderProgram::GetId() const {
        return m_iProgramId;
    }

    void CShaderProgram::SetModel(const glm::mat3& modelMat) {
        Use();
        glUniformMatrix3fv(m_iUniformModelLoc, 1, GL_FALSE, glm::value_ptr(modelMat));
    }

    void CShaderProgram::SetWorld(const glm::mat3& worldMat) {
        Use();
        glUniformMatrix3fv(m_iUniformWorldLoc, 1, GL_FALSE, glm::value_ptr(worldMat));
    }

    void CShaderProgram::SetPosition(const glm::vec2& posVec) {
        Use();
        glVertexAttrib2fv(m_iAttribPositionLoc, glm::value_ptr(posVec));
    }

    void CShaderProgram::Use() {
        glUseProgram(m_iProgramId);
    }

    CShaderProgram::~CShaderProgram() {
        if (m_iProgramId == 0) return;
        glDeleteProgram(m_iProgramId);
        spdlog::debug("Deleted shader program id {}", m_iProgramId);
        m_iProgramId = 0;
    }

    int CShaderProgram::GetLocations() {
        try {
            m_iUniformWorldLoc = GetUniformLocation("world");
            m_iUniformModelLoc = GetUniformLocation("model");
            m_iAttribPositionLoc = GetAttribLocation("position");
            spdlog::debug("Program {} locations: world={} model={} position={}",
                GetId(), m_iUniformWorldLoc, m_iUniformModelLoc, m_iAttribPositionLoc);
            return 0;
        }
        catch (std::exception e) {
            throw e;
        }
    }
}
