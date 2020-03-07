#pragma once
class Logger
{
public:
	static void Trace(const char* message, ...);
	static void Log(const char* message, ...);
	static void Error(const char* message, ...);
	static void Warn(const char* message, ...);
	static void Fatal(const char* message, ...);
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
