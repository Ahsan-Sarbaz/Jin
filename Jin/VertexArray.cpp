#include "pch.h"
#include "VertexArray.h"

VertexArray::VertexArray()
{
}

void VertexArray::Init()
{
    glGenVertexArrays(1, &m_id);
}

void VertexArray::Bind()
{
    glBindVertexArray(m_id);
}

void VertexArray::Unbind()
{
    glBindVertexArray(0);
}

void VertexArray::PushVertexBuffer(const VertexBuffer& buffer)
{
    const VertexAttrib* attribs = buffer.GetAttribs();
    u32 attribsCount = buffer.GetAttribsCount();
    Bind();
    buffer.Bind();
    for(u32 i = 0; i < attribsCount; ++i)
    {
        glEnableVertexAttribArray(attribs[i].index);
        glVertexAttribPointer(attribs[i].index, attribs[i].size, attribs[i].type, attribs[i].normalized, attribs[i].stride, attribs[i].pointer);
    }
    Unbind();
    buffer.Unbind();
}

void VertexArray::PushIndexBuffer(const IndexBuffer& buffer)
{
    Bind();
    buffer.Bind();
    Unbind();
}