#include <iostream>
#include "Application.h"
#include <glm\gtc\type_ptr.hpp>
#include "Input.h"
#include "PerspectiveCamera.h"
#include "Light.h"
#include "BatchRenderer2D.h"
#include "Logger.h"
#include "Time.h"
#include "SpriteSheet.h"
#include "stb_truetype.h"

class MainLayer : public Layer
{
private:
	Vec4 clearColor = { 0.8f,0.8f,0.8f,1 };
	bool show_properties = true;
	OrthographicCamera cam = OrthographicCamera(1280, 720);
	
	Texture tex;
	SpriteSheet spriteSheet;

public:
	MainLayer()
		:Layer("main_layer")
	{

	}

	virtual void Start() override
	{
		BatchRenderer2D::Init();
		BatchRenderer2D::SetCamera(&cam);

		tex= Texture("textures/explosion.png", 0);
		spriteSheet = SpriteSheet(&tex, 99.888f, 95.222f);
	}

	virtual void Update() override
	{
		glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//cam.Tick();
		
		float time = Time::GetSeconds();
		static float index = 0;
		
		if (show_properties)
		{
			ImGui::Begin("Properties", &show_properties);

			ImGui::Text("Framerate : %f", ImGui::GetIO().Framerate);
			ImGui::Text("Time : %f", time);
			ImGui::ColorEdit4("Clear Color", clearColor.data);

			ImGui::Text("Draw Calls %d", BatchRenderer2D::GetDrawCount());
			ImGui::Text("Quad Count %d", BatchRenderer2D::GetQuadCount());


			ImGui::End();
		}

		BatchRenderer2D::ResetStates();
		
		BatchRenderer2D::Begin();
		
		BatchRenderer2D::DrawQuad({ 0,0 }, { 400, 400 }, spriteSheet, (u32)index);
		// TODO:: Spritesheet animation
		
		BatchRenderer2D::End();
		
		BatchRenderer2D::Flush();
	}

	virtual void End() override
	{

	}
};

i32 main()
{
	Application app;
	ApplicationConfiguration config = {};
	
	config.width = 1280;
	config.height = 720;
	config.title = "Window";
	config.vsync = 0;
	config.api = GraphicsAPI::DX11;

	if (!app.Init(config))
	{
		JIN_FATAL("Application Failed to Initialize");
		return EXIT_FAILURE;
	}
	app.AddLayer(new MainLayer);

	if (!app.Run())
	{
		JIN_FATAL("Application Failed to Run");
		return EXIT_FAILURE;
	}
}