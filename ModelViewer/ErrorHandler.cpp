#include <string>
#include <cstring>

#include "ErrorHandler.h"

/// <summary>Prints a yellow warning message to the console.</summary>
void ErrorHandler::LogWarning(const std::string& message)
{
    std::cerr << "\x1b[33mWarning: " << message << "\x1b[0m\n";
}

// Print a yellow warning message to the console with file and line information
void ErrorHandler::LogWarning(const std::string& message, const char* file, int line)
{
    std::string fileName = ExtractFileName(file);
    
    std::cerr << "\x1b[33mWarning in " << fileName << "(" << line << "): " << message << "\x1b[0m\n";
}

/// <summary>Prints a red error message to the console.</summary>
void ErrorHandler::LogError(const std::string& message)
{
    std::cerr << "\x1b[31mError: " << message << "\x1b[0m\n";
}

/// <summary>Prints a red error message to the console with file and line information.</summary>
void ErrorHandler::LogError(const std::string& message, const char* file, int line)
{
    std::string fileName = ExtractFileName(file);
    std::cerr << "\x1b[31mError in " << fileName << "(" << line << "): " << message << "\x1b[0m\n";
}

/// <summary>Takes an ErrorType enum member as argument. Prints an red error message to the console.</summary>
void ErrorHandler::LogError(const MessageType& errorType)
{
    auto iterator = errorTypeToString.find(errorType);
    if (iterator != errorTypeToString.end())
        std::cerr << "\x1b[31mError: " << iterator->second << "\x1b[0m\n";
    else
        std::cerr << "\x1b[31mError: Unknown error type.\x1b[0m\n";
}

/// <summary>Takes an ErrorType enum member and a file and line as arguments. Prints an red error message to the console.</summary>
void ErrorHandler::LogError(const MessageType& errorType, const char* file, int line)
{
    std::string fileName = ExtractFileName(file);
    
    auto iterator = errorTypeToString.find(errorType);
    if (iterator != errorTypeToString.end())
        std::cerr << "\x1b[31mError in file:\x1b[32m " << fileName << "(" << line << "): \x1b[31m" << iterator->second << "\x1b[0m\n";
    else
        std::cerr << "\x1b[31mError: Unknown error type.\x1b[0m\n";
}

/// <summary>Takes an ErrorType enum member and a message as arguments. Prints an red error message to the console.</summary>
void ErrorHandler::LogError(const std::string& message, const MessageType& errorType)
{
    auto iterator = errorTypeToString.find(errorType);
    if (iterator != errorTypeToString.end())
        std::cerr << "\x1b[31mError: " << message << "" << iterator->second << "\x1b[0m\n";
    else
        std::cerr << "\x1b[31mError: Unknown error type.\x1b[0m\n";
}

/// <summary>Takes an ErrorType enum member, a message and a file and line as arguments. Prints an red error message to the console.</summary>
void ErrorHandler::LogError(const std::string& message, const MessageType& errorType, const char* file, int line)
{
    std::string fileName = ExtractFileName(file);
    
    auto iterator = errorTypeToString.find(errorType);
    if (iterator != errorTypeToString.end())
        std::cerr << "\x1b[31mError in file:\x1b[32m " << fileName << "(" << line << "): \x1b[31m"<< message << "" << iterator->second << "\x1b[0m\n";
    else
        std::cerr << "\x1b[31mError: Unknown error type.\x1b[0m\n";
}

/// <summary>Takes an ErrorType enum member and a message as arguments. Prints an red error message to the console.</summary>
void ErrorHandler::LogError(const MessageType& errorType, const std::string& message)
{
    auto iterator = errorTypeToString.find(errorType);
    if (iterator != errorTypeToString.end())
        std::cerr << "\x1b[31mError: " << iterator->second << "" << message << "\x1b[0m\n";
    else
        std::cerr << "\x1b[31mError: Unknown error type.\x1b[0m\n";
}

/// <summary>Takes an ErrorType enum member, a message and a file and line as arguments. Prints an red error message to the console.</summary>
void ErrorHandler::LogError(const MessageType& errorType, const std::string& message, const char* file, int line)
{
    std::string fileName = ExtractFileName(file);
    
    auto iterator = errorTypeToString.find(errorType);
    if (iterator != errorTypeToString.end())
        std::cerr << "\x1b[31mError in file:\x1b[32m " << fileName << "(" << line << "): \x1b[31m"<< message << "" << iterator->second << "\x1b[0m\n";
    else
        std::cerr << "\x1b[31mError: Unknown error type.\x1b[0m\n";
}

/// <summary>Prints a white message to the console.</summary>
void ErrorHandler::LogInfo(const char* message)
{
    std::cout << "LogInfo: " << message << "\n";
}

std::string  ErrorHandler::ExtractFileName(const char* filePath)
{
    const char* lastSlash = strrchr(filePath, '/');
    const char* lastBackSlash = strrchr(filePath, '\\');
    
    const char* lastSeparator = (lastBackSlash > lastSlash) ? lastBackSlash : lastSlash;

    if (lastSeparator != nullptr)
    {
        return lastSeparator + 1;
    }
    return filePath; 
}
