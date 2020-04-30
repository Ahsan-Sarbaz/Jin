#include "pch.h"
#include "LayerSharedData.h"
#include "Logger.h"

std::unordered_map<const char*, void*> LayerSharedData::m_dataPointers = {};
glm::mat4 LayerSharedData::ZeroPtr = glm::mat4(0.0f);

void* LayerSharedData::Get(const char* name)
{
    auto it = m_dataPointers.find(name);
    if(it != m_dataPointers.end())
    {
        return it->second;
    }
    else
    {
        Logger::Error("Failed to get data %s. sending 0", name);
        return &ZeroPtr;
    }
}

void LayerSharedData::Set(const char* name, void* ptr)
{
    m_dataPointers.insert(std::pair<const char*, void*>(name, ptr));
}