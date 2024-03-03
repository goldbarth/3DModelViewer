// Added by me to handle errors and warnings in a more organized and convenient way.
#ifndef ERROR_HANDLER_H
#define ERROR_HANDLER_H

#include <unordered_map>
#include <iostream>
#include <string>

enum class MessageType : char
{
    SUCCESS = 0,
    GLAD_INIT_FAILED,
    RUN_VIEWPORT_FAILED,
    DRAW_AMBIENT_FAILED,
    ENGINE_INIT_FAILED,
    GLFW_WINDOW_INIT_FAILED,
    VERTEX_SHADER_COMPILATION_FAILED,
    FRAGMENT_SHADER_COMPILATION_FAILED,
    ASSIMP_IMPORT_FAILED,
    ASSIMP_MESH_READ_FAILED,
    SHADER_PROGRAM_LINK_FAILED,
    SHADER_COMPILATION_FAILED,
    DATA_MANAGER_INIT_FAILED,
    FILESTREAM_STILL_OPEN,
    FAILED_LOAD_TEXTURE,
    READ_FILE_FAILED,
    COUNT,
};

class ErrorHandler
{
public:
    template <typename T>
    static void Log(const T& message);
    static void LogWarning(const std::string& message);
    static void LogWarning(const std::string& message, const char* file, int line);
    static void LogError(const std::string& message);
    static void LogError(const std::string& message, const char* file, int line);
    static void LogError(const MessageType& errorType);
    static void LogError(const MessageType& errorType, const char* file, int line);
    static void LogError(const std::string& message, const MessageType& errorType);
    static void LogError(const std::string& message, const MessageType& errorType, const char* file, int line);
    static void LogError(const MessageType& errorType, const std::string& message);
    static void LogError(const MessageType& errorType, const std::string& message, const char* file, int line);
    static void LogInfo(const char* message);
    static std::string ExtractFileName(const char* filePath);

private:
    // This is a map of ErrorType enum members and their corresponding error messages.
    // Hash tables(unsorted map) is preferable used for fast lookups instead of binary search trees(map).
    inline static std::unordered_map<MessageType, std::string> errorTypeToString =
    {
        { MessageType::GLFW_WINDOW_INIT_FAILED, "GLFW window initialization failed." },
        { MessageType::GLAD_INIT_FAILED, "Failed to initialize GLAD." },
        { MessageType::RUN_VIEWPORT_FAILED, "Failed to run viewport." },
        { MessageType::ENGINE_INIT_FAILED, "Failed to initialize engine." },
        { MessageType::VERTEX_SHADER_COMPILATION_FAILED, "Failed to compile vertex shader." },
        { MessageType::SHADER_PROGRAM_LINK_FAILED, "Failed to link shader program." },
        { MessageType::READ_FILE_FAILED, "File to read was not found." },
        { MessageType::FILESTREAM_STILL_OPEN, "Filestream is still open." },
        { MessageType::DATA_MANAGER_INIT_FAILED, "Data manager is null." },
        { MessageType::DRAW_AMBIENT_FAILED, "Failed to draw ambient. The uniform variable could not be found." },
        { MessageType::FAILED_LOAD_TEXTURE, "Failed to load the texture." },
        { MessageType::ASSIMP_MESH_READ_FAILED, "Failed to read mesh at Model-Loader." },
        { MessageType::SHADER_COMPILATION_FAILED, "Failed to compile shader." },
        { MessageType::FRAGMENT_SHADER_COMPILATION_FAILED, "Failed to compile fragment shader." },
        { MessageType::ASSIMP_IMPORT_FAILED, "Failed to import model at Model-Loader." },
    };
};

/// <summary>Prints a white message to the console.</summary>
template <typename T>
void ErrorHandler::Log(const T& message)
{
    std::cout << message << "\n";
}

#endif // ERROR_HANDLER_H
