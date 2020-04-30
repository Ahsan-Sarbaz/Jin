#include "pch.h"
#include "Application.h"
#include "Time.h"
#include "Logger.h"

#define JIN_IMGUI 1

Application* Application::m_instance = nullptr;

Application::Application()
{
	m_instance = this;
}

Application::~Application()
{
#if JIN_IMGUI
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
#endif // JIN_NO_IMGUI
}

static void window_size_callback(GLFWwindow* window, i32 Width, i32 Height)
{
	glViewport(0, 0, Width, Height);
    ApplicationConfiguration* config = Application::Get()->GetConfig();
    
    config->Width = Width;
    config->Height = Height;
}

static void glfw_error_callback(int code, const char* message)
{
    Logger::Fatal("GLFW ERROR: %d, %s", code, message);
}

static void glErrorCallback(GLenum source,
                            GLenum type,
                            GLuint id,
                            GLenum severity,
                            GLsizei length,
                            const GLchar *message,
                            const void *userParam)
{
    Logger::Error("GL ERROR %d : %s", id, message);
}

bool Application::Init(const ApplicationConfiguration& config)
{
	m_appConfig = config;
	
    glfwSetErrorCallback(glfw_error_callback);
    
	if (!InitGLFW())
    {
        Logger::Fatal("Failed to init GLFW! Cannot continue");
        return false;
	}
    
    int major = 4;
    int minor = 3;
	
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	m_window = glfwCreateWindow(m_appConfig.Width, m_appConfig.Height, m_appConfig.Title, 0, 0);
    if (!m_window)
    {
        Logger::Fatal("Failed to create Window with GL verion %d.%d", major, minor);
        return false;
    }
    
    glfwSetWindowUserPointer(m_window, this);
    
	glfwMakeContextCurrent(m_window);
    glewExperimental = true;
	if (!InitGLEW())
    {
        Logger::Fatal("Failed to init GLEW! Cannot continue");
        return false;
    }
    
	m_isOpen = true;
    if(glDebugMessageCallbackARB != nullptr)
    {
        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        glDebugMessageCallback(glErrorCallback, nullptr);
        glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
    }
    else
    {
        Logger::Log("glDebugMessageCallback not Supported!");
    }
    
	glfwSetWindowSizeCallback(m_window, window_size_callback);
    
#if JIN_IMGUI
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
	ImGui::StyleColorsDark();
	ImGuiStyle& style = ImGui::GetStyle();
	ImGui_ImplGlfw_InitForOpenGL(m_window, true);
	ImGui_ImplOpenGL3_Init("#version 130");
#endif // JIN_NO_IMGUI
    
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_DEPTH_TEST);
    
	glfwSwapInterval(m_appConfig.Vsync ? 1 : 0);
    
	return true;
}

bool Application::Run()
{
	for (auto layer : m_layers)
	{
		layer.second->Start();
	}
    
	while (!glfwWindowShouldClose(m_window))
	{
		glfwPollEvents();
        
		f32 time = (f32)glfwGetTime();
		f32 dt = time - m_lastFrameTime;
		m_lastFrameTime = time;
		Time::Tick(dt);
        
		//m_isOpen = !glfwWindowShouldClose(m_window.GetHandle());
        
#if JIN_IMGUI
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
#endif // JIN_NO_IMGUI
        
		for (auto layer : m_layers)
		{
			layer.second->Update();
		}
        
#if JIN_IMGUI
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		ImGuiIO& io = ImGui::GetIO();
		
#endif // JIN_NO_IMGUI
        
		glfwSwapBuffers(m_window);
	}
    
	for (auto layer : m_layers)
	{
		layer.second->End();
	}
    
	return true;
}

void Application::AddLayer(Layer* layer)
{
	m_layers.insert(std::pair<cstr, Layer*>(layer->GetName(), layer));
}

void Application::RemoveLayer(Layer* layer)
{
	m_layers.erase(layer->GetName());
}

bool Application::InitGLEW()
{
	if (glewInit() != GLEW_OK)
		return false;
	return true;
}

bool Application::InitGLFW()
{
	if (glfwInit() != GLFW_TRUE)
		return false;
	return true;
}
