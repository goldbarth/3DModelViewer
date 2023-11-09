#include <iostream>

#include "ErrorHandler.h"

/// <summary>Takes an ErrorType enum member as argument. Prints an red error message to the console.</summary>
void ErrorHandler::LogError(const ErrorType& errorType)
{
    auto iterator = errorTypeToString.find(errorType);
    if (iterator != errorTypeToString.end())
        std::cerr << "\x1b[31mError: " << iterator->second << "\x1b[0m\n";
    else
        std::cerr << "\x1b[31mError: Unknown error type.\x1b[0m\n";
}

void ErrorHandler::LogError(const std::string& message, const ErrorType& errorType)
{
    auto iterator = errorTypeToString.find(errorType);
    if (iterator != errorTypeToString.end())
        std::cerr << "\x1b[31mError: " << message << "" << iterator->second << "\x1b[0m\n";
    else
        std::cerr << "\x1b[31mError: Unknown error type.\x1b[0m\n";
}

/// <summary>Prints an red error message to the console.</summary>
void ErrorHandler::LogError(const std::string& message)
{
    std::cerr << "\x1b[31mError: " << message << "\x1b[0m\n";
}
