#ifndef _INDEX_BUFFER_H
#define _INDEX_BUFFER_H
#include "pch.h"

class IndexBuffer
{
    private:
    u32 m_id;
    u32 m_indexCount;
    
    public:
    IndexBuffer();
    IndexBuffer(u32* data, u32 count);
    
    void Bind() const;
    void Unbind() const;
    
    JIN_INLINE const u32 GetID() const { return m_id; }
    JIN_INLINE const u32 GetIndexCount() const { return m_indexCount; }
};

#endif //_INDEX_BUFFER_H
