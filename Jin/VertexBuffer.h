#ifndef _VERTEX_BUFFER_H
#define _VERTEX_BUFFER_H
#include "pch.h"

struct VertexAttrib
{
    u32 index;
    i32 size;
    i32 type;
    bool normalized;
    i32 stride;
    const void* pointer;
};

class VertexBuffer
{
    private:
    u32 m_id;
    VertexAttrib* m_attribs;
    u32 m_attribsCount;
    
    public:
    VertexBuffer();
    VertexBuffer(void* data, u32 size);
    
    void SetBufferAttribs(VertexAttrib* attribs, u32 count);
    void SetBufferSubData(void* data, u32 size);
    
    void Bind() const;
    void Unbind() const;
    
    JIN_INLINE const VertexAttrib* GetAttribs() const { return m_attribs; }
    JIN_INLINE const u32 GetAttribsCount() const { return m_attribsCount; }
    JIN_INLINE const u32 GetID() const { return m_id; }
};

#endif //_VERTEX_BUFFER_H
