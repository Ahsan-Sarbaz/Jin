#ifndef _VERTEX_ARRAY_H
#define _VERTEX_ARRAY_H
#include "pch.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

class VertexArray
{
    private:
    u32 m_id;
    
    public:
    VertexArray();
    
    void Init();
    
    void Bind();
    void Unbind();
    
    void PushVertexBuffer(const VertexBuffer& buffer);
    void PushIndexBuffer(const IndexBuffer& buffer);
    
    JIN_INLINE const u32 GetID() const { return m_id; }
};

#endif //_VERTEX_ARRAY_H
