// =============================================================================
// AIEngine2D - Logger System
// =============================================================================
#pragma once

#include <cstdio>
#include <cstdarg>

#ifdef _WIN32
#include <windows.h>
#endif

namespace SebF2DEngine
{

enum class LogLevel
{
    Info,
    Warning,
    Error
};

class Logger
{
public:
    static void log(LogLevel level, const char* format, ...)
    {
        // Set console color based on level
        setConsoleColor(level);

        // Print level prefix
        const char* prefix = getLevelPrefix(level);
        printf("%s ", prefix);

        // Print message
        va_list args;
        va_start(args, format);
        vprintf(format, args);
        va_end(args);

        printf("\n");

        // Reset color
        resetConsoleColor();
    }

private:
    static const char* getLevelPrefix(LogLevel level)
    {
        switch (level)
        {
            case LogLevel::Info:    return "[INFO]";
            case LogLevel::Warning: return "[WARNING]";
            case LogLevel::Error:   return "[ERROR]";
            default:                return "[UNKNOWN]";
        }
    }

    static void setConsoleColor(LogLevel level)
    {
#ifdef _WIN32
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        switch (level)
        {
            case LogLevel::Info:
                SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                break;
            case LogLevel::Warning:
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                break;
            case LogLevel::Error:
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
                break;
        }
#else
        switch (level)
        {
            case LogLevel::Info:    printf("\033[32m"); break; // Green
            case LogLevel::Warning: printf("\033[33m"); break; // Yellow
            case LogLevel::Error:   printf("\033[31m"); break; // Red
        }
#endif
    }

    static void resetConsoleColor()
    {
#ifdef _WIN32
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
#else
        printf("\033[0m");
#endif
    }
};

// Convenience macros
#define LOG_INFO(...)    SebF2DEngine::Logger::log(SebF2DEngine::LogLevel::Info, __VA_ARGS__)
#define LOG_WARNING(...) SebF2DEngine::Logger::log(SebF2DEngine::LogLevel::Warning, __VA_ARGS__)
#define LOG_ERROR(...)   SebF2DEngine::Logger::log(SebF2DEngine::LogLevel::Error, __VA_ARGS__)

} // namespace SebF2DEngine
