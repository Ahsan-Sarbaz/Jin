#include "Logger.h"
#include <stdarg.h>
#include <stdio.h>
#include <string>

static void printMessage(const char* type, const char* message, va_list args)
{
	vprintf((std::string(type) + message + "\n").c_str(), args);
}

void Logger::Trace(const char* message, ...)
{
	va_list args;
	va_start(args, message);
	printMessage("[TRACE] ", message, args);
}

void Logger::Log(const char* message, ...)
{
	va_list args;
	va_start(args, message);
	printMessage("[LOG] ", message, args);
}

void Logger::Error(const char* message, ...)
{
	va_list args;
	va_start(args, message);
	printMessage("[ERROR] ", message, args);
}

void Logger::Warn(const char* message, ...)
{
	va_list args;
	va_start(args, message);
	printMessage("[Warn] ", message, args);
}

void Logger::Fatal(const char* message, ...)
{
	va_list args;
	va_start(args, message);
	printMessage("[Fatal] ", message, args);
}