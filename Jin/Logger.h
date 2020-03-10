#pragma once
#include "Types.h"

class Logger
{
public:
	static void Trace(cstr message, ...);
	static void Log(cstr message, ...);
	static void Error(cstr message, ...);
	static void Warn(cstr message, ...);
	static void Fatal(cstr message, ...);
};


#if _DEBUG
#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)
#define AT " => [" TOSTRING(__LINE__) " " __FUNCSIG__ " => "__FILE__ "]"
#define JIN_TRACE(msg) Logger::Trace(msg AT)
#define JIN_LOG(msg) Logger::Log(msg AT)
#define JIN_ERROR(msg) Logger::Error(msg AT)
#define JIN_WARN(msg) Logger::Warn(msg AT)
#define JIN_FATAL(msg) Logger::Fatal(msg AT)
#else
#define JIN_TRACE(msg)
#define JIN_LOG(msg)
#define JIN_ERROR(msg)
#define JIN_WARN(msg)
#define JIN_FATAL(msg)
#endif // _DEBUG
