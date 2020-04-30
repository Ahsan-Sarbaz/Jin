#include "pch.h"
#include "Logger.h"

static void printMessage(cstr type, cstr message, va_list args)
{
	vprintf((std::string(type) + message + "\n").c_str(), args);
}

void Logger::Trace(cstr message, ...)
{
	va_list args;
	va_start(args, message);
	printMessage("[TRACE] ", message, args);
}

void Logger::Log(cstr message, ...)
{
	va_list args;
	va_start(args, message);
	printMessage("[LOG] ", message, args);
}

void Logger::Error(cstr message, ...)
{
	va_list args;
	va_start(args, message);
	printMessage("[ERROR] ", message, args);
}

void Logger::Warn(cstr message, ...)
{
	va_list args;
	va_start(args, message);
	printMessage("[Warn] ", message, args);
}

void Logger::Fatal(cstr message, ...)
{
	va_list args;
	va_start(args, message);
	printMessage("[Fatal] ", message, args);
}
