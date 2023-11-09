#ifndef ERROR_HANDLER_H
#define ERROR_HANDLER_H

#include <unordered_map>
#include <string>

enum class ErrorType : char
{
    SUCCESS = 0,
    GLFW_WINDOW_INIT_FAILED,
    GLAD_INIT_FAILED,
    RUN_VIEWPORT_FAILED,
    CREATE_ENGINE_FAILED,
    COUNT
};

class ErrorHandler
{
public:
    static void LogError(const ErrorType& errorType);
    static void LogError(const std::string& message, const ErrorType& errorType);
    static void LogError(const std::string& message);
    
private:
    // This is a map of ErrorType enum members and their corresponding error messages.
    // Hash tables(unsorted map) is preferable used for fast lookups instead of binary search trees(map).
    inline static std::unordered_map<ErrorType, std::string> errorTypeToString =
    {
        {ErrorType::GLFW_WINDOW_INIT_FAILED, "GLFW window initialization failed."},
        {ErrorType::GLAD_INIT_FAILED, "Failed to initialize GLAD."},
        {ErrorType::RUN_VIEWPORT_FAILED, "Failed to run viewport."},
        {ErrorType::CREATE_ENGINE_FAILED, "Failed to create engine."}
    };
};

#endif // !ERROR_HANDLER_H
