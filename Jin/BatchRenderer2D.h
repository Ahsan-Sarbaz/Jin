#pragma once
#include "Types.h"
#include "Texture.h"
#include <unordered_map>
#include "Shader.h"
#include "Camera.h"
#include "Maths.h"

struct Vertex
{
	Vec3 position;
	Vec4 color;
	Vec2 texCoord;
	u32 texture;
};

struct RendererState
{
	bool Initiated = false;
	u32 VAO;
	u32 VBO;
	u32 IBO;
	Vertex* Buffer;
	Vertex* BufferPtr = nullptr;
	u32 IndexCount = 0;
	u32 QuadCount = 0;
	u32 DrawCount = 0;
	i32 MaxTextureUnits = 0;
	i32 TextureUnit = 1;
	Texture WhiteTexture;
	std::unordered_map<i32, i32> TextureUnitCache;
	Shader* CurrentShader;
	Camera* CurrentCamera;
};

class BatchRenderer2D
{
public:
	
	static void Init();
	static void Shutdown();

	static void Begin();
	static void End();
	static void Flush();

	static void DrawQuad(const Vec2& pos, const Vec2& size, const Vec4& color);
	static void DrawQuad(const Vec2& pos, const Vec2& size, const Texture& texture);

	static const u32 GetDrawCount();
	static const u32 GetQuadCount();

	static Shader* GetShader();
	static void SetShader(Shader* shader);

	static void SetCamera(Camera* camera);
	static Camera* GetCamera();

	static void ResetStates();
};