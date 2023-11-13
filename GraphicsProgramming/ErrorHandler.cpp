#include "ErrorHandler.h"

/// <summary>Prints a yellow warning message to the console.</summary>
void ErrorHandler::LogWarning(const std::string& message)
{
    std::cout << "\x1b[33mWarning: " << message << "\x1b[0m\n";
}

/// <summary>Prints a red error message to the console.</summary>
void ErrorHandler::LogError(const std::string& message)
{
    std::cerr << "\x1b[31mError: " << message << "\x1b[0m\n";
}

/// <summary>Takes an ErrorType enum member as argument. Prints an red error message to the console.</summary>
void ErrorHandler::LogError(const ErrorType& errorType)
{
    auto iterator = errorTypeToString.find(errorType);
    if (iterator != errorTypeToString.end())
        std::cerr << "\x1b[31mError: " << iterator->second << "\x1b[0m\n";
    else
        std::cerr << "\x1b[31mError: Unknown error type.\x1b[0m\n";
}

/// <summary>Takes an ErrorType enum member and a message as arguments. Prints an red error message to the console.</summary>
void ErrorHandler::LogError(const std::string& message, const ErrorType& errorType)
{
    auto iterator = errorTypeToString.find(errorType);
    if (iterator != errorTypeToString.end())
        std::cerr << "\x1b[31mError: " << message << "" << iterator->second << "\x1b[0m\n";
    else
        std::cerr << "\x1b[31mError: Unknown error type.\x1b[0m\n";
}

/// <summary>Takes an ErrorType enum member and a message as arguments. Prints an red error message to the console.</summary>
void ErrorHandler::LogError(const ErrorType& errorType, const std::string& message)
{
    auto iterator = errorTypeToString.find(errorType);
    if (iterator != errorTypeToString.end())
        std::cerr << "\x1b[31mError: " << iterator->second << "" << message << "\x1b[0m\n";
    else
        std::cerr << "\x1b[31mError: Unknown error type.\x1b[0m\n";
}
