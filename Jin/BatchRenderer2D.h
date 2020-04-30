#pragma once
#include "pch.h"
#include "Texture.h"
#include "Shader.h"
#include "Camera.h"
#include "SpriteSheet.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "stb_truetype.h"

struct Vertex
{
	Vec3 Position;
	Vec4 Color;
	Vec2 UV;
    float Texture;
};

struct RendererState
{
    bool Initiated = false;
    VertexArray VAO;
    VertexBuffer VBO;
    IndexBuffer IBO;
	Vertex* Buffer;
	Vertex* BufferPtr = nullptr;
	u32 IndexCount = 0;
	u32 QuadCount = 0;
	u32 DrawCount = 0;
	i32 MaxTextureUnits = 0;
    float TextureUnit = 1;
	Texture WhiteTexture;
	std::unordered_map<i32, float> TextureUnitCache;
	Shader* CurrentShader;
	Camera* CurrentCamera;
    Vec4 ClearColor = {0, 0, 0, 1};
    Texture FontTexture;
    stbtt_bakedchar StbBackedCharData[96];
};

class BatchRenderer2D
{
    public:
	
	static void Init();
	static void Shutdown();
    
	static void Begin();
	static void End();
    
	static void DrawQuad(const Vec2& pos, const Vec2& size, const Vec4& color);
	static void DrawQuad(const Vec2& pos, const Vec2& size, const Texture& texture, const Rect& rect = {0,0,1,1});
	static void DrawQuad(const Vec2& pos, const Vec2& size, const SpriteSheet& spriteSheet, u32 cell);
    static void DrawText(const char* text, const Vec2& pos, const Vec4& color);
    
    static void SetClearColor(const Vec4& color);
    JIN_INLINE static void Clear() { glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); }
    
    static void SetShader(Shader* shader);
    static Shader* GetShader();
    
    static void SetCamera(Camera* camera);
    static Camera* GetCamera();
    
    static const u32 GetDrawCount();
    static const u32 GetQuadCount();
    static void ResetStates();
};