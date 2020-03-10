#include <iostream>
#include "Application.h"
#include <glm\gtc\type_ptr.hpp>
#include "Input.h"
#include "PerspectiveCamera.h"
#include "Light.h"
#include "BatchRenderer2D.h"
#include "Logger.h"

#include "stb_truetype.h"

class MainLayer : public Layer
{
private:
	Vec4 clearColor = { 0.8f,0.8f,0.8f,1 };
	bool show_properties = true;
	OrthographicCamera cam = OrthographicCamera(1920, 1080);
	
	Texture spriteSheet;

public:
	MainLayer()
		:Layer("main_layer")
	{

	}

	virtual void Start() override
	{
		BatchRenderer2D::Init();
		BatchRenderer2D::SetCamera(&cam);

		spriteSheet = Texture("textures/spritesheet.png", 0);
	}

	virtual void Update() override
	{
		glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		cam.Tick();

		if (show_properties)
		{
			ImGui::Begin("Properties", &show_properties);

			ImGui::Text("Framerate : %f", ImGui::GetIO().Framerate);

			ImGui::ColorEdit4("Clear Color", clearColor.data);

			ImGui::Text("Draw Calls %d", BatchRenderer2D::GetDrawCount());
			ImGui::Text("Quad Count %d", BatchRenderer2D::GetQuadCount());


			ImGui::End();
		}

		BatchRenderer2D::ResetStates();

		BatchRenderer2D::Begin();
	
		BatchRenderer2D::DrawQuad({ 0,0 }, { 500,500 }, spriteSheet);

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
	
	config.width = 1920;
	config.height = 1080;
	config.title = "Window";
	config.vsync = 0;

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