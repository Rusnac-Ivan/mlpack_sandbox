#include "Application.h"


Application& Application::Run(int argc, const char** argv, const char* version, const char* title)
{
    static Application  instance;
    return instance;
}

void Application::MainLoop()
{

}