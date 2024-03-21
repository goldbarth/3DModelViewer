#include "Application.h"

int main(int argc, char* argv[])
{
    const auto pApplication = std::make_unique<Application>();
    pApplication->Run();
    
    return static_cast<int>(MessageType::SUCCESS);
}