#include "Application.h"

Application::Application(unsigned int width, unsigned int height, const char* title)
{
	mView.Create(width, height, title);
    MainLoop();
	mView.Destroy();
}

Application& Application::Run(unsigned int width, unsigned int height, const char* title)
{
    static Application  instance(width, height, title);
    return instance;
}

void Application::MainLoop()
{
	mView.OnInitialize();
	while (mView.WindowIsOpen())
	{
		mView.OnUpdate();
	}
	mView.OnFinalize();
}