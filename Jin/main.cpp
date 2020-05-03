#include "pch.h"
#include "Jin.h"

class DebugLayer: public Layer
{
	private:
	bool show_properties = true;
	Vec4* clearColor;
	Vec2 mouse;
	
	public:
	DebugLayer()
		:Layer("debug_layer")
	{
		
	}
	
	virtual void Start() override
	{
		clearColor = (Vec4*)LayerSharedData::Get("clearColor");
	}
	
	virtual void Update() override
	{
		clearColor = (Vec4*)LayerSharedData::Get("clearColor");
		
		static float boundTexture;
		glGetFloatv(GL_TEXTURE_BINDING_2D, &boundTexture);

		if (show_properties)
		{
			ImGui::Begin("Properties", &show_properties);
			ImGui::Text("Framerate : %f", ImGui::GetIO().Framerate);
			ImGui::ColorEdit4("Clear Color", clearColor->data);
			ImGui::Text("Draw Calls %d", RendererStats::GetDrawCount());
			ImGui::Text("Quad Count %d", RendererStats::GetQuadCount());
			ImGui::Text("Texture Bound %f", boundTexture);
			ImGui::End();
		}
	}
	
	virtual void End() override
	{
		
	}
};

class MainLayer : public Layer
{
	private:
	Vec4 clearColor = { 0.8f,0.8f,0.8f,1 };
	OrthographicCamera cam = OrthographicCamera(800, 600);
	
	Texture runningTexture;
	SpriteSheet runningSpriteSheet;
	Animation runningAnim;
	
	public:
	MainLayer()
		:Layer("main_layer")
	{
		
	}
	
	virtual void Start() override
	{
		BatchRenderer2D::Init();
		BatchRenderer2D::SetCamera(&cam);
				
		runningTexture = Texture("textures/running.png", 0);
		
		runningSpriteSheet = SpriteSheet(&runningTexture, 108.0f, 140.0f);
		
		runningAnim = Animation(&runningSpriteSheet, 0, 8, 0.5f);
		
		LayerSharedData::Set("clearColor", &clearColor);
	}
	
	virtual void Update() override
	{
		
		BatchRenderer2D::SetClearColor(clearColor);
		BatchRenderer2D::Clear();
		
		cam.Tick();
		
		float time = Time::GetSeconds();
		
		runningAnim.Update();
		
		RendererStats::ResetStats();
		
		BatchRenderer2D::Begin();
		runningAnim.Draw({0,0}, {100, 100});
		BatchRenderer2D::End();

	}
	
	virtual void End() override
	{
	}
};

i32 main()
{
	Application app;
	ApplicationConfiguration config = {};
	
	config.Width = 800;
	config.Height = 600;
	config.Title = "Window";
	config.Vsync = 1;
	
	if (!app.Init(config))
	{
		JIN_FATAL("Application Failed to Initialize");
		return EXIT_FAILURE;
	}
	
	const u8* renderer = glGetString(GL_RENDERER);
	const u8* version = glGetString(GL_VERSION);
	Logger::Trace("%s , %s", renderer, version);
	
	//app.AddLayer(new DebugLayer);
	app.AddLayer(new MainLayer);
	
	if (!app.Run())
	{
		JIN_FATAL("Application Failed to Run");
		return EXIT_FAILURE;
	}
}
