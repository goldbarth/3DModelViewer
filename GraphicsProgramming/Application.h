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
    
    FileDataHandler* pData = new FileDataHandler();
    Engine* pEngine = new Engine(pData);
};

#endif // !APPLICATION_H
