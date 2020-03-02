#include <iostream>
#include "Application.h"
#include "Renderer2D.h"
#include <glm\gtc\type_ptr.hpp>
#include "Input.h"
#include "PerspectiveCamera.h"
#include "Light.h"
#include "BatchRenderer2D.h"

int main()
{
	Application app;
	ApplicationConfiguration config = {};
	
	config.width = 1920;
	config.height = 1080;
	config.title = "Window";
	config.vsync = 0;
	
	if (!app.Init(config)) return 1;
	if (!app.Run()) return 2;

	
	bool show_properties = true;
	glm::vec4 clearColor = {0.8f,0.8f,0.8f,1};

	OrthographicCamera cam(1920, 1080);
	
	BatchRenderer2D batchRenderer;

	std::vector<Texture*> m_textures;

	m_textures.emplace_back(new Texture ("textures/1"));
	m_textures.emplace_back(new Texture ("textures/2"));
	m_textures.emplace_back(new Texture ("textures/3"));
	m_textures.emplace_back(new Texture ("textures/4"));
	m_textures.emplace_back(new Texture ("textures/5"));
	m_textures.emplace_back(new Texture ("textures/6"));
	m_textures.emplace_back(new Texture ("textures/7"));
	m_textures.emplace_back(new Texture ("textures/8"));
	m_textures.emplace_back(new Texture ("textures/9"));
	m_textures.emplace_back(new Texture ("textures/10"));
	m_textures.emplace_back(new Texture ("textures/11"));
	m_textures.emplace_back(new Texture ("textures/12"));
	m_textures.emplace_back(new Texture ("textures/13"));
	m_textures.emplace_back(new Texture ("textures/14"));
	m_textures.emplace_back(new Texture ("textures/15"));
	m_textures.emplace_back(new Texture ("textures/16"));
	m_textures.emplace_back(new Texture ("textures/17"));
	m_textures.emplace_back(new Texture ("textures/18"));
	m_textures.emplace_back(new Texture ("textures/19"));
	m_textures.emplace_back(new Texture ("textures/20"));
	m_textures.emplace_back(new Texture ("textures/21"));
	m_textures.emplace_back(new Texture ("textures/22"));
	m_textures.emplace_back(new Texture ("textures/23"));
	m_textures.emplace_back(new Texture ("textures/24"));
	m_textures.emplace_back(new Texture ("textures/25"));
	m_textures.emplace_back(new Texture ("textures/26"));
	m_textures.emplace_back(new Texture ("textures/27"));
	m_textures.emplace_back(new Texture ("textures/28"));
	m_textures.emplace_back(new Texture ("textures/29"));
	m_textures.emplace_back(new Texture ("textures/30"));
	m_textures.emplace_back(new Texture ("textures/31"));


	m_textures.emplace_back(new Texture("textures/1"));
	m_textures.emplace_back(new Texture("textures/2"));
	m_textures.emplace_back(new Texture("textures/3"));
	m_textures.emplace_back(new Texture("textures/4"));
	m_textures.emplace_back(new Texture("textures/5"));
	m_textures.emplace_back(new Texture("textures/6"));
	m_textures.emplace_back(new Texture("textures/7"));
	m_textures.emplace_back(new Texture("textures/8"));
	m_textures.emplace_back(new Texture("textures/9"));
	m_textures.emplace_back(new Texture("textures/10"));
	m_textures.emplace_back(new Texture("textures/11"));
	m_textures.emplace_back(new Texture("textures/12"));
	m_textures.emplace_back(new Texture("textures/13"));
	m_textures.emplace_back(new Texture("textures/14"));
	m_textures.emplace_back(new Texture("textures/15"));
	m_textures.emplace_back(new Texture("textures/16"));
	m_textures.emplace_back(new Texture("textures/17"));
	m_textures.emplace_back(new Texture("textures/18"));
	m_textures.emplace_back(new Texture("textures/19"));
	m_textures.emplace_back(new Texture("textures/20"));
	m_textures.emplace_back(new Texture("textures/21"));
	m_textures.emplace_back(new Texture("textures/22"));
	m_textures.emplace_back(new Texture("textures/23"));
	m_textures.emplace_back(new Texture("textures/24"));
	m_textures.emplace_back(new Texture("textures/25"));
	m_textures.emplace_back(new Texture("textures/26"));
	m_textures.emplace_back(new Texture("textures/27"));
	m_textures.emplace_back(new Texture("textures/28"));
	m_textures.emplace_back(new Texture("textures/29"));
	m_textures.emplace_back(new Texture("textures/30"));
	m_textures.emplace_back(new Texture("textures/31"));

	while (app.IsOpen())
	{
		app.PollEvents();
	
		app.Tick();
				
		cam.Tick();
		
		glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		if (show_properties)
		{
			ImGui::Begin("Properties", &show_properties);
			
			ImGui::Text("Framerate : %f", ImGui::GetIO().Framerate);

			ImGui::ColorEdit4("Clear Color", glm::value_ptr(clearColor));
			
			ImGui::Text("Draw Calls %d", batchRenderer.GetDrawCount());
			ImGui::Text("Quad Count %d", batchRenderer.GetQuadCount());
			
			
			ImGui::End();
		}
	

		batchRenderer.ResetStates();

		batchRenderer.Begin();

		float size = 5;
		float gutter = size / 2;
		float finalSize = size + gutter;

		for (float y = 0; y < 1000; y++)
		{
			for (float x = 0; x < 50; x++)
			{
				float r = 5;
				batchRenderer.DrawQuad({ x + size * x + r, y + size * y + r }, { finalSize, finalSize}, { 1,1,0,1 });
			}
		}

		batchRenderer.End();

		batchRenderer.GetShader()->Bind();
		batchRenderer.GetShader()->SetUniformMat4("u_ViewProjection", cam.GetViewProjectionMatrix());
		
		batchRenderer.Flush();

		
		app.SwapBuffers();

	}
}