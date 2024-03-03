#include "Engine.h"

int main(int argc, char* argv[])
{
    const auto pEngine = std::make_unique<Engine>();
    pEngine->Initialize();
    pEngine->Run();
    pEngine->Finalize();
    
    return static_cast<int>(MessageType::SUCCESS);
}