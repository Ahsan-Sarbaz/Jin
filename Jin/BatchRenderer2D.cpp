#include "pch.h"
#include "BatchRenderer2D.h"
#include "Logger.h"
#define STB_TRUETYPE_IMPLEMENTATION
#include <stb_truetype.h>

#define MAX_QUAD_COUNT 1024
#define MAX_VERT_COUNT MAX_QUAD_COUNT * 4
#define MAX_IND_COUNT MAX_QUAD_COUNT * 6

static RendererState state = {};

void BatchRenderer2D::Init()
{
	if (state.Initiated)
	{
		return;
	}
    
	state.Initiated = true;
    
	state.CurrentShader = new Shader("shaders/batchvs.glsl", "shaders/batchfs.glsl");
    
    state.VAO.Init();
    
    VertexAttrib attribs[4] =
    {
        {0, 3, GL_FLOAT, false, sizeof(Vertex), (void*)offsetof(Vertex, Position)},
        {1, 4, GL_FLOAT, false, sizeof(Vertex), (void*)offsetof(Vertex, Color)},
        {2, 2, GL_FLOAT, false, sizeof(Vertex), (void*)offsetof(Vertex, UV)},
        {3, 1, GL_FLOAT, false, sizeof(Vertex), (void*)offsetof(Vertex, Texture)},
    };
    
    state.VBO = VertexBuffer(nullptr, sizeof(Vertex) * MAX_VERT_COUNT);
    state.VBO.SetBufferAttribs(attribs, 4);
    
    state.VAO.PushVertexBuffer(state.VBO);
    
	u32* indices = new u32[MAX_IND_COUNT];
	u32 offset = 0;
	for (size_t i = 0; i < MAX_IND_COUNT; i += 6)
	{
		indices[i + 0] = 0 + offset;
		indices[i + 1] = 1 + offset;
		indices[i + 2] = 2 + offset;
        
		indices[i + 3] = 2 + offset;
		indices[i + 4] = 3 + offset;
		indices[i + 5] = 0 + offset;
        
		offset += 4;
	}
    
    state.IBO = IndexBuffer(indices, MAX_IND_COUNT);
    state.VAO.PushIndexBuffer(state.IBO);
    
    delete[] indices;
    
	state.Buffer = new Vertex[MAX_VERT_COUNT];
    
	glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &state.MaxTextureUnits);
	u8 whiteTextureData[4] = { 0xff, 0xff, 0xff, 0xff };
	state.WhiteTexture = Texture(&whiteTextureData);
    
	state.WhiteTexture.SetSlot(0);
    
	state.CurrentShader->Bind();
	auto  location = glGetUniformLocation(state.CurrentShader->GetID(), "u_textures");
	i32* samplers = new i32[state.MaxTextureUnits];
	for (i32 i = 0; i < state.MaxTextureUnits; ++i)
	{
		samplers[i] = i;
	}
	glUniform1iv(location, state.MaxTextureUnits, samplers);
	delete[] samplers;
	state.CurrentShader->Unbind();
    
    unsigned char* ttf_buffer = new unsigned char[1<<20];
    unsigned char* temp_bitmap = new unsigned char[512*512];
    
    const char* fontFilePath = "fonts/font.ttf";
    FILE* fontFile = fopen(fontFilePath, "rb");
    if(fontFile)
    {
        fread(ttf_buffer, 1, 1<<20, fontFile);
        stbtt_BakeFontBitmap(ttf_buffer,0, 32.0, temp_bitmap,512,512, 32,96, state.StbBackedCharData);
        state.FontTexture = Texture(temp_bitmap, 512, 512, GL_RED, GL_ALPHA);
    }
    else
    {
        Logger::Error("Failed to open %s", fontFilePath);
    }

    delete[] ttf_buffer;
    delete[] temp_bitmap;
}

void BatchRenderer2D::Shutdown()
{
	delete state.CurrentShader;
	delete[] state.Buffer;
}

void BatchRenderer2D::Begin()
{
	state.BufferPtr = state.Buffer;
}

void BatchRenderer2D::End()
{
    if (state.IndexCount > 0)
    {
        GLsizeiptr size = (unsigned char*)state.BufferPtr - (unsigned char*)state.Buffer;
        state.VBO.SetBufferSubData(state.Buffer, size);
        
        state.CurrentShader->Bind();
        state.CurrentShader->SetUniformMat4("u_ViewProjection", state.CurrentCamera->GetViewProjectionMatrix());
        
        state.VAO.Bind();
        glDrawElements(GL_TRIANGLES, state.IndexCount, GL_UNSIGNED_INT, nullptr);
        state.IndexCount = 0;
        state.DrawCount++;
    }
}

inline static void AddQuadToBuffer(const Vec2& pos, const Vec2& size, const Vec4& Color, const Rect& rect, float texture)
{
    state.BufferPtr->Position = { pos.x, pos.y, 0.0f };
    state.BufferPtr->Color = Color;
    state.BufferPtr->UV = { rect.x, rect.y };
    state.BufferPtr->Texture = texture;
    state.BufferPtr++;
    
    state.BufferPtr->Position = { pos.x + size.x, pos.y, 0.0f };
    state.BufferPtr->Color = Color;
    state.BufferPtr->UV = { rect.w, rect.y };
    state.BufferPtr->Texture = texture;
    state.BufferPtr++;
    
    state.BufferPtr->Position = { pos.x + size.x, pos.y + size.y, 0.0f };
    state.BufferPtr->Color = Color;
    state.BufferPtr->UV = { rect.w, rect.h };
    state.BufferPtr->Texture = texture;
    state.BufferPtr++;
    
    state.BufferPtr->Position = { pos.x, pos.y + size.y, 0.0f };
    state.BufferPtr->Color = Color;
    state.BufferPtr->UV = { rect.x, rect.h };
    state.BufferPtr->Texture = texture;
    state.BufferPtr++;
    
    state.IndexCount += 6;
    
    state.QuadCount++;
}

void BatchRenderer2D::DrawQuad(const Vec2& pos, const Vec2& size, const Vec4& color)
{
    
    if (state.IndexCount >= MAX_IND_COUNT)
    {
        End();
        Begin();
    }
    
    state.WhiteTexture.Bind();
    
    Rect rect = {0,0,1,1};
    
    AddQuadToBuffer(pos, size, color, rect, 0.0f);
}

void BatchRenderer2D::DrawQuad(const Vec2& pos, const Vec2& size, const Texture& texture, const Rect& rect)
{
    if (state.IndexCount >= MAX_IND_COUNT || state.TextureUnit >= state.MaxTextureUnits)
    {
        End();
        Begin();
        state.TextureUnit = 0;
    }
    
    float TextureSlot = 0;
    if (state.TextureUnitCache.find(texture.GetID()) == state.TextureUnitCache.end())
    {
        //not found
        state.TextureUnitCache[texture.GetID()] = state.TextureUnit;
        TextureSlot = state.TextureUnit;
        state.TextureUnit++;
    }
    else
    {
        TextureSlot = state.TextureUnitCache[texture.GetID()];
        state.TextureUnit++;
    }
    
    texture.Bind(TextureSlot);
    
    AddQuadToBuffer(pos, size, {1,1,1,1}, rect, TextureSlot);
}

void BatchRenderer2D::DrawQuad(const Vec2& pos, const Vec2& size, const SpriteSheet& spriteSheet, u32 cell)
{
    DrawQuad(pos, size, *spriteSheet.GetTexture(), spriteSheet.GetSpriteRect(cell));
}

void BatchRenderer2D::DrawText(const char* text, const Vec2& pos, const Vec4& color)
{
    float x = pos.x;
    float y = pos.y;
    
    while (*text) {
        if (*text >= 32 && *text < 128) {
            
            stbtt_aligned_quad q;
            stbtt_GetBakedQuad(state.StbBackedCharData, 512,512, *text-32, &x,&y,&q,1);//1=opengl & d3d10+,0=d3d9
            if(*text == ' ')
            {
                ++text;
                continue;
            }
            if (state.IndexCount >= MAX_IND_COUNT)
            {
                End();
                Begin();
            }
            
            float TextureSlot = 0.0f;
            if (state.TextureUnitCache.find(state.FontTexture.GetID()) == state.TextureUnitCache.end())
            {
                //not found
                state.TextureUnitCache[state.FontTexture.GetID()] = state.TextureUnit;
                TextureSlot = state.TextureUnit;
                state.TextureUnit++;
            }
            else
            {
                TextureSlot = state.TextureUnitCache[state.FontTexture.GetID()];
                state.TextureUnit++;
            }
            
            state.FontTexture.Bind(TextureSlot);
            
            state.BufferPtr->Position = { q.x0, q.y0, 0.0f };
            state.BufferPtr->Color = color;
            state.BufferPtr->UV = { q.s0, q.t0 };
            state.BufferPtr->Texture = TextureSlot;
            state.BufferPtr++;
            
            state.BufferPtr->Position = { q.x1, q.y0, 0.0f };
            state.BufferPtr->Color = color;
            state.BufferPtr->UV = { q.s1, q.t0 };
            state.BufferPtr->Texture = TextureSlot;
            state.BufferPtr++;
            
            state.BufferPtr->Position = { q.x1, q.y1, 0.0f };
            state.BufferPtr->Color = color;
            state.BufferPtr->UV = { q.s1, q.t1 };
            state.BufferPtr->Texture = TextureSlot;
            state.BufferPtr++;
            
            state.BufferPtr->Position = { q.x0, q.y1, 0.0f };
            state.BufferPtr->Color = color;
            state.BufferPtr->UV = { q.s0, q.t1 };
            state.BufferPtr->Texture = TextureSlot;
            state.BufferPtr++;
            
            state.IndexCount += 6;
            
            ++state.QuadCount;
        }
        ++text;
    }
}


const u32 BatchRenderer2D::GetDrawCount()
{
    return state.DrawCount;
}

const u32 BatchRenderer2D::GetQuadCount()
{
    return state.QuadCount;
}

Shader* BatchRenderer2D::GetShader()
{
    return state.CurrentShader;
}

void BatchRenderer2D::SetShader(Shader* shader)
{
    state.CurrentShader = shader;
}

void BatchRenderer2D::SetCamera(Camera* camera)
{
    state.CurrentCamera = camera;
}

Camera* BatchRenderer2D::GetCamera()
{
    return state.CurrentCamera;
}

void BatchRenderer2D::ResetStates()
{
    state.DrawCount = 0;
    state.QuadCount = 0;
}

void BatchRenderer2D::SetClearColor(const Vec4& color)
{
    if(state.ClearColor != color)
    {
        glClearColor(color.r, color.g, color.b, color.a);
        state.ClearColor = color;
    }
}
