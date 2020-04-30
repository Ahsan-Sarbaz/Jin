#ifndef _LAYER_SHARED_DATA_H
#define _LAYER_SHARED_DATA_H
#include "pch.h"

class LayerSharedData
{
    private:
    static std::unordered_map<const char*, void*> m_dataPointers;
    static glm::mat4 ZeroPtr;
    public:
    static void* Get(const char*);
    static void Set(const char*, void*);
};

#endif //_LAYER_SHARED_DATA_H
