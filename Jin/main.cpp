#include <iostream>
#include "Application.h"
#include "Renderer2D.h"
#include <glm\ext\matrix_clip_space.hpp>
#include <glm\gtc\type_ptr.hpp>
#include "Input.h"

int main()
{
	Application app;
	ApplicationConfiguration config = {};
	
	config.width = 1280;
	config.height = 1024;
	config.title = "Window";
	config.vsync = 1;
	
	if (!app.Init(config)) return 1;
	if (!app.Run()) return 2;

	Renderer2D renderer;
	RendererConfig rendererConfig = {};
	renderer.Init(rendererConfig);
	
	bool show_properties = true;
	glm::vec4 clearColor = {0.8f,0.8f,0.8f,1};

	glm::vec3 position = {400,300,0};
	glm::vec3 size = {800,600,1};
	glm::vec4 color = {1,1,1,1};

	Texture t("textures\\test.png");

	Scene scene;
	auto projection = glm::ortho(0.0f, (float)config.width, (float)config.height, 0.0f, -1.0f, 1.0f);
	scene.SetProjection(projection);

	while (app.IsOpen())
	{
		app.PollEvents();
		app.Tick();

		renderer.Clear(clearColor);
		
		scene.Update(app.GetWindow());

		renderer.BeginScene(scene);

		if (show_properties)
		{
			ImGui::Begin("Properties", &show_properties);
			
			ImGui::Text("Framerate : %f", ImGui::GetIO().Framerate);
			ImGui::SliderFloat3("Position", glm::value_ptr(position), 0, 800);
			ImGui::SliderFloat3("Size", glm::value_ptr(size), 1, 10000);
			ImGui::ColorEdit4("Color", glm::value_ptr(color));
			ImGui::ColorEdit4("Clear Color", glm::value_ptr(clearColor));
			ImGui::Text("Texture");
			ImGui::Image((ImTextureID)t.GetID(), { 100,100 });
			
			ImGui::End();
		}

		renderer.DrawQuad(position, size, color, t);

		renderer.EndScene();

		app.SwapBuffers();
	}
}