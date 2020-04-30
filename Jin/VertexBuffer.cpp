#include "pch.h"
#include "VertexBuffer.h"

VertexBuffer::VertexBuffer()
{
    
}

VertexBuffer::VertexBuffer(void* data, u32 size)
{
    glGenBuffers(1, &m_id);
    glBindBuffer(GL_ARRAY_BUFFER, m_id);
    if(data == nullptr)
        glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
    else
        glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::SetBufferAttribs(VertexAttrib* attribs, u32 count)
{
    m_attribs = attribs;
    m_attribsCount = count;
}

void VertexBuffer::SetBufferSubData(void* data, u32 size)
{
    Bind();
    glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
}

void VertexBuffer::Bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, m_id);
}

void VertexBuffer::Unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}