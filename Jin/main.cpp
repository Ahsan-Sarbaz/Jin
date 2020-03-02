#include <iostream>
#include "Application.h"
#include <glm\gtc\type_ptr.hpp>
#include "Input.h"
#include "PerspectiveCamera.h"
#include "Light.h"
#include "BatchRenderer2D.h"

class MainLayer : public Layer
{
private:
	glm::vec4 clearColor = { 0.8f,0.8f,0.8f,1 };
	bool show_properties = true;
	OrthographicCamera cam = OrthographicCamera(1920, 1080);
	
public:
	MainLayer()
		:Layer("main_layer")
	{

	}

	virtual void Start() override
	{
		BatchRenderer2D::Init();
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

			ImGui::ColorEdit4("Clear Color", glm::value_ptr(clearColor));

			ImGui::Text("Draw Calls %d", BatchRenderer2D::GetDrawCount());
			ImGui::Text("Quad Count %d", BatchRenderer2D::GetQuadCount());


			ImGui::End();
		}

		BatchRenderer2D::ResetStates();

		BatchRenderer2D::Begin();

		float size = 5;
		float gutter = size / 2;
		float finalSize = size + gutter;

		for (float y = 0; y < 1000; y++)
		{
			for (float x = 0; x < 50; x++)
			{
				float r = 5;
				BatchRenderer2D::DrawQuad({ x + size * x + r, y + size * y + r }, { finalSize, finalSize }, { 1,0,1,1 });
			}
		}

		BatchRenderer2D::End();

		BatchRenderer2D::GetShader()->Bind();
		BatchRenderer2D::GetShader()->SetUniformMat4("u_ViewProjection", cam.GetViewProjectionMatrix());

		BatchRenderer2D::Flush();
	}

	virtual void End() override
	{

	}
};

int main()
{
	Application app;
	ApplicationConfiguration config = {};
	
	config.width = 1920;
	config.height = 1080;
	config.title = "Window";
	config.vsync = 0;
	
	if (!app.Init(config)) return 1;

	app.AddLayer(new MainLayer);

	if (!app.Run()) return 2;
}