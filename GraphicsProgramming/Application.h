#ifndef APPLICATION_H
#define APPLICATION_H

#include <memory>

#include "Engine.h"

class Application
{
public:
    Application() : pEngine(std::make_unique<Engine>()) {  }
    void Run() const;
    
private:
    std::unique_ptr<Engine> pEngine;
};

#endif // !APPLICATION_H
