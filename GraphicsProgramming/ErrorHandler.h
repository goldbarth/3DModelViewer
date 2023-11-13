#ifndef ERROR_HANDLER_H
#define ERROR_HANDLER_H

#include <unordered_map>
#include <iostream>
#include <string>

enum class ErrorType : char
{
    SUCCESS = 0,
    GLAD_INIT_FAILED,
    RUN_VIEWPORT_FAILED,
    DRAW_AMBIENT_FAILED,
    CREATE_ENGINE_FAILED,
    GLFW_WINDOW_INIT_FAILED,
    VERTEX_SHADER_COMPILATION_FAILED,
    FRAGMENT_SHADER_COMPILATION_FAILED,
    SHADER_PROGRAM_LINK_FAILED,
    DATA_MANAGER_INIT_FAILED,
    FILESTREAM_STILL_OPEN,
    READ_FILE_FAILED,
    COUNT,
};

class ErrorHandler
{
public:
    template <typename T>
    static void Log(const T& message);
    static void LogWarning(const std::string& message);
    static void LogError(const ErrorType& errorType);
    static void LogError(const std::string& message, const ErrorType& errorType);
    static void LogError(const ErrorType& errorType, const std::string& message);
    static void LogError(const std::string& message);
    
private:
    // This is a map of ErrorType enum members and their corresponding error messages.
    // Hash tables(unsorted map) is preferable used for fast lookups instead of binary search trees(map).
    inline static std::unordered_map<ErrorType, std::string> errorTypeToString =
    {
        {ErrorType::GLFW_WINDOW_INIT_FAILED, "GLFW window initialization failed."},
        {ErrorType::GLAD_INIT_FAILED, "Failed to initialize GLAD."},
        {ErrorType::RUN_VIEWPORT_FAILED, "Failed to run viewport."},
        {ErrorType::CREATE_ENGINE_FAILED, "Failed to create engine."},
        {ErrorType::VERTEX_SHADER_COMPILATION_FAILED, "Failed to compile vertex shader."},
        {ErrorType::SHADER_PROGRAM_LINK_FAILED, "Failed to link shader program."},
        {ErrorType::READ_FILE_FAILED, "File to read was not found."},
        {ErrorType::FILESTREAM_STILL_OPEN, "Filestream is still open."},
        {ErrorType::DATA_MANAGER_INIT_FAILED, "Data manager is null."},
        {ErrorType::DRAW_AMBIENT_FAILED, "Failed to draw ambient. The uniform variable could not be found."},
    };
};

/// <summary>Prints a white message to the console.</summary>
template <typename T>
void ErrorHandler::Log(const T& message)
{
    std::cout << message << "\n";
}

#endif // !ERROR_HANDLER_H
