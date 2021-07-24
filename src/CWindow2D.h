#pragma once

#include <string>
#include <glm/mat3x3.hpp>
#include "glad.h"
#include <GLFW/glfw3.h>
#include "common.h"
#include "CBasicWindow.h"

namespace rbe {

    void window_resize_cb(GLFWwindow* w, int width, int height);

    void window_key_cb(GLFWwindow* w, int key, int scancode, int action, int mods);

    class CWindow2D: public CBasicWindow
    {
        GLFWwindow* m_pWindow{ nullptr };
        std::string m_sTitle{ "" };
        int m_iWidth{ 640 };
        int m_iHeight{ 480 };
        glm::mat3 m_m3World{ 1.0f };
    public:
        CWindow2D(int width, int height, const char* title);
        virtual ~CWindow2D();
        void SetBgColor(float r, float g, float b, float a);
        virtual void OnDraw() {};
        void SetShouldClose();
        bool IsShouldClose() override;
        void ProcessKey(int key, int scancode, int action, int mods) override;
        void Resize(int w, int h) override;
        void Draw() override;
        int GetWidth() const override;
        int GetHeight() const override;
    private:
        void UpdateWorldMatrix();
        void SetCurrent();
    };

    using CWindow2DPtr = std::shared_ptr<CWindow2D>;
}
