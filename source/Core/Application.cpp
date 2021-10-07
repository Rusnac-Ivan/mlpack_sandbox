#include "Application.h"

Application::Application()
{

    MainLoop();
}

Application& Application::Run(unsigned int width, unsigned int height, const char* title)
{
    static Application  instance;
    return instance;
}

void Application::MainLoop()
{
	/*mView.OnInitialize();
	while (mWindow.WindowIsOpen())
	{
		mWindow.PollEvents();


		mView.OnUpdate();

		mWindow.RenderGUI();
		mWindow.SwapBuffers();
	}
	mView.OnFinalize();*/
}