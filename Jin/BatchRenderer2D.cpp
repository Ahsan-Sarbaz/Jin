#include "pch.h"
#include "BatchRenderer2D.h"
#include "Logger.h"
#include "RendererStats.h"

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
        {3, 1, GL_FLOAT, false, sizeof(Vertex), (void*)offsetof(Vertex, TextureSlot)},
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
        RendererStats::IncDrawCount();
    }
}

inline static void AddQuadToBuffer(const Vec2& pos, const Vec2& size, const Vec4& Color, const Rect& rect, float texture)
{
    state.BufferPtr->Position = { pos.x, pos.y, 0.0f };
    state.BufferPtr->Color = Color;
    state.BufferPtr->UV = { rect.x, rect.y };
    state.BufferPtr->TextureSlot = texture;
    state.BufferPtr++;

    state.BufferPtr->Position = { pos.x + size.x, pos.y, 0.0f };
    state.BufferPtr->Color = Color;
    state.BufferPtr->UV = { rect.w, rect.y };
    state.BufferPtr->TextureSlot = texture;
    state.BufferPtr++;

    state.BufferPtr->Position = { pos.x + size.x, pos.y + size.y, 0.0f };
    state.BufferPtr->Color = Color;
    state.BufferPtr->UV = { rect.w, rect.h };
    state.BufferPtr->TextureSlot = texture;
    state.BufferPtr++;

    state.BufferPtr->Position = { pos.x, pos.y + size.y, 0.0f };
    state.BufferPtr->Color = Color;
    state.BufferPtr->UV = { rect.x, rect.h };
    state.BufferPtr->TextureSlot = texture;
    state.BufferPtr++;

    state.IndexCount += 6;

    RendererStats::IncQuadCount();
}

void BatchRenderer2D::DrawQuad(const Vec2& pos, const Vec2& size, const Vec4& color)
{

    if (state.IndexCount >= MAX_IND_COUNT)
    {
        End();
        Begin();
    }

    state.WhiteTexture.Bind();

    Rect rect = { 0,0,1,1 };

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

    AddQuadToBuffer(pos, size, { 1,1,1,1 }, rect, TextureSlot);
}

void BatchRenderer2D::DrawQuad(const Vec2& pos, const Vec2& size, const SpriteSheet& spriteSheet, u32 cell)
{
    DrawQuad(pos, size, *spriteSheet.GetTexture(), spriteSheet.GetSpriteRect(cell));
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

void BatchRenderer2D::SetClearColor(const Vec4& color)
{
    if (state.ClearColor != color)
    {
        glClearColor(color.r, color.g, color.b, color.a);
        state.ClearColor = color;
    }
}