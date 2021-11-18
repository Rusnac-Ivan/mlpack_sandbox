#include <mlpack_sandbox-version.h>
#include <MLTest.h>
#include <iostream>

#include<Core/Application.h>


int main(int argc, char* argv[])
{
    std::cout << "Project Name: " << MLPACK_SANDBOX_PROJECT_NAME << std::endl;
    std::cout << "Project Description: " << MLPACK_SANDBOX_PROJECT_DESCRIPTION << std::endl;
    //mv::MLTest app;
    //app.Run();
    //test_open_blas();
    Application& app = Application::Run(1280, 720, "Opengl Window");
    return 0;
}
