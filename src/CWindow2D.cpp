#include <spdlog/spdlog.h>
#include "CWindow2D.h"

namespace rbe {
    void window_resize_cb(GLFWwindow* w, int width, int height)
    {
        auto* wnd = static_cast<CWindow2D*>(glfwGetWindowUserPointer(w));
        if (!wnd)
        {
            spdlog::error("Error resizing window - empty user pointer");
            return;
        }
        wnd->Resize(width, height);
    }

    void window_key_cb(GLFWwindow* w, int key, int scancode, int action, int mods)
    {
        auto* wnd = static_cast<CWindow2D*>(glfwGetWindowUserPointer(w));
        if (!wnd)
        {
            spdlog::error("Error processing kb event - empty user pointer");
            return;
        }
        wnd->ProcessKey(key, scancode, action, mods);
    }

    void window_close_cb(GLFWwindow* w)
    {
        auto p = static_cast<CWindow2D*>(glfwGetWindowUserPointer(w));
        std::shared_ptr<CWindow2D> wnd(p);
        RemoveWindow(wnd);
    }

    RBE_RESULT Init2D()
    {
		spdlog::info("RBE: initializing 2d stuff");
		try
		{
			auto dshv = CShader{ "shaders\\default.vs", EShaderType::Vertex };
			auto dshf = CShader{ "shaders\\default.fs", EShaderType::Fragment };
			auto shader = std::make_shared<CShaderProgram>(dshv, dshf);
			auto textshader = std::make_shared<CShaderProgram>(CShader{ "shaders\\font.vs", EShaderType::Vertex },
				CShader{ "shaders\\font.fs", EShaderType::Fragment });
            auto primitiveShader = std::make_shared<CShaderProgram>(CShader{ "shaders\\primitive.vs", EShaderType::Vertex },
                CShader{ "shaders\\primitive.fs", EShaderType::Fragment });
			if (SetDefaultShader(shader) != 0 || SetDefaultTextShader(textshader) != 0 || 
                SetDefaultPrimitiveShader(primitiveShader) != 0)
			{
				throw std::runtime_error{ "Error setting default shaders" };
			}
			glm::mat3 fontModel{ 1.0f };
			fontModel[1][1] = -1.0f;
			textshader->SetModel(fontModel);
            InitFonts();
			auto font = std::make_shared<CFont>("fonts\\VelaSans-Regular.ttf", 16);
            ReleaseFonts();
			if (SetDefaultFont(font) != 0)
			{
				throw std::runtime_error{ "Error setting default font" };
			}
			return RBE_RESULT::SUCCESS;
		}
		catch (std::exception& e)
		{
			spdlog::error("Failed to initialize 2d: {}", e.what());
			return RBE_RESULT::FAILURE;
		}
	}

    void Release2D()
    {
        SetDefaultShader(nullptr);
        SetDefaultTextShader(nullptr);
        SetDefaultPrimitiveShader(nullptr);
        SetDefaultFont(nullptr);
    }

    CWindow2D::CWindow2D(int width, int height, const char* title)
        : 
        m_sTitle{ title },
        m_iWidth{ width },
        m_iHeight{ height }
    {
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        m_pWindow = glfwCreateWindow(m_iWidth, m_iHeight, m_sTitle.c_str(), nullptr, nullptr);
        if (!m_pWindow)
        {
            spdlog::error("Unable to create window {} {}x{}", m_sTitle, m_iWidth, m_iHeight);
            throw std::runtime_error{ "Unable to create window" };
        }
        SetCurrent();
        glfwSetWindowUserPointer(m_pWindow, this);
        glfwSetWindowSizeCallback(m_pWindow, window_resize_cb);
        glfwSetKeyCallback(m_pWindow, window_key_cb);
		gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        if (Init2D() == RBE_RESULT::FAILURE)
        {
            throw std::runtime_error{ "Error initializing 2D stuff" };
        }
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glfwSwapInterval(1);
        glViewport(0, 0, GetWidth(), GetHeight());

        Resize(m_iWidth, m_iHeight);

        //AddWindow(std::shared_ptr<CWindow2D>(this));

    }

    CWindow2D::~CWindow2D()
    {
        Release2D();
        glfwDestroyWindow(m_pWindow);
        spdlog::debug("~CWindow2D");
    }

    bool CWindow2D::IsShouldClose()
    {
        return glfwWindowShouldClose(m_pWindow) == GLFW_TRUE;
    }

    void CWindow2D::SetShouldClose()
    {
        glfwSetWindowShouldClose(m_pWindow, GLFW_TRUE);
    }

    void CWindow2D::ProcessKey(int key, int scancode, int action, int mods)
    {
        if (action == GLFW_PRESS && key == GLFW_KEY_ESCAPE)
        {
            glfwSetWindowShouldClose(m_pWindow, GLFW_TRUE);
        }
    }

    void CWindow2D::Resize(int w, int h)
    {
        m_iWidth  = w;
        m_iHeight = h;
        UpdateWorldMatrix();
    }

    void CWindow2D::SetCurrent()
    {
        glfwMakeContextCurrent(m_pWindow);
    }

    void CWindow2D::Draw()
    {
        SetCurrent();
        glViewport(0, 0, GetWidth(), GetHeight());
        glClear(GL_COLOR_BUFFER_BIT);
        OnDraw();
        glfwSwapBuffers(m_pWindow);
    }

    int CWindow2D::GetWidth() const
    {
        return m_iWidth;
    }

    int CWindow2D::GetHeight() const
    {
        return m_iHeight;
    }

    void CWindow2D::SetBgColor(float r, float g, float b, float a)
    {
        SetCurrent();
        glClearColor(r, g, b, a);
    }


    void CWindow2D::UpdateWorldMatrix()
    {
        m_m3World = glm::mat3{ 2.0f / m_iWidth, 0.0f,             0.0f,
                               0.0f,           -2.0f / m_iHeight, 0.0f,
                              -1.0f,           -1.0f,             1.0f };
        GetDefaultShader()->SetWorld(m_m3World);
        GetDefaultTextShader()->SetWorld(m_m3World);
        GetDefaultPrimitiveShader()->SetWorld(m_m3World);
    }
}