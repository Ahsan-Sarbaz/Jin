#include <iostream>
#include "Application.h"
#include "Renderer2D.h"
#include <glm\gtc\type_ptr.hpp>
#include "Input.h"
#include "PerspectiveCamera.h"


int main()
{
	Application app;
	ApplicationConfiguration config = {};
	
	config.width = 1920;
	config.height = 1080;
	config.title = "Window";
	config.vsync = 1;
	
	if (!app.Init(config)) return 1;
	if (!app.Run()) return 2;

	Renderer2D renderer;
	RendererConfig rendererConfig = {};
	renderer.Init(rendererConfig);
	
	bool show_properties = true;
	glm::vec4 clearColor = {0.8f,0.8f,0.8f,1};

	glm::vec3 position = {400,300, 0};
	glm::vec3 size = {800,600,1};
	glm::vec4 color = {1,1,1,1};

	Texture t("textures\\test.png");

	Scene scene;

	OrthographicCamera cam(1920, 1080);
	PerspectiveCamera perspectiveCam(1920, 1080, 0.1f, 100, 90);

	scene.SetCamera(&cam);
	bool perspective = false;

	Material mat;
	mat.SetDiffuse(color);
	mat.SetTexture(t);

	
	while (app.IsOpen())
	{
		app.PollEvents();
		app.Tick();

		renderer.Clear(clearColor);
		
		if (perspective)
		{
			scene.SetCamera(&perspectiveCam);
		}
		else
		{
			scene.SetCamera(&cam);
			position.z = 0;

		}

		scene.Update(app.GetWindow());

		renderer.BeginScene(scene);

		if (show_properties)
		{
			ImGui::Begin("Properties", &show_properties);
			
			ImGui::Text("Framerate : %f", ImGui::GetIO().Framerate);
			ImGui::SliderFloat3("Position", glm::value_ptr(position), 0, 800);
			ImGui::SliderFloat3("Size", glm::value_ptr(size), 1, 10000);
			ImGui::ColorEdit4("Color", glm::value_ptr(mat.GetDiffuse()));
			ImGui::ColorEdit4("Clear Color", glm::value_ptr(clearColor));
			ImGui::Text("Texture");
			ImGui::Image((ImTextureID)mat.GetTexture().GetID(), { 100,100 });
			
			ImGui::Checkbox("Perspective", &perspective);

			ImGui::End();
		}
	
		renderer.DrawQuad(position, size, mat);
 
		renderer.EndScene();

		app.SwapBuffers();
	}
}