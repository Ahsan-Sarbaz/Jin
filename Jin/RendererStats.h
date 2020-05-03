#pragma once
#include "pch.h"

class RendererStats
{
private:
	static u32 DrawCount;
	static u32 QuadCount;

public:
	JIN_INLINE static void IncDrawCount() { DrawCount++; }
	JIN_INLINE static void IncQuadCount() { QuadCount++; }
	JIN_INLINE static void ResetStats() { DrawCount = 0; QuadCount = 0; }
	JIN_INLINE static u32 GetDrawCount() { return DrawCount; }
	JIN_INLINE static u32 GetQuadCount() { return QuadCount; }
};