#ifndef APPLICATION_H
#define APPLICATION_H

#include "FileDataHandler.h"
#include "Engine.h"

class Application
{
public:
    int Run();
private:
    ErrorType errorType = ErrorType::ENGINE_INIT_FAILED;

    std::unique_ptr<FileDataHandler> pData = std::make_unique<FileDataHandler>();
    std::unique_ptr<Engine> pEngine = std::make_unique<Engine>(std::move(pData));
};

#endif // !APPLICATION_H
