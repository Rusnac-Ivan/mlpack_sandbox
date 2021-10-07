#include <mlpack_sandbox-version.h>
#include <MLTest.h>
#include <iostream>

#include<Core/Application.h>

//#include <openblas/cblas.h>

/*
void test_open_blas()
{
    int i = 0;
    double A[6] = { 1.0,2.0,1.0,-3.0,4.0,-1.0 };
    double B[6] = { 1.0,2.0,1.0,-3.0,4.0,-1.0 };
    double C[9] = { .5,.5,.5,.5,.5,.5,.5,.5,.5 };
    cblas_dgemm(CblasColMajor, CblasNoTrans, CblasTrans, 3, 3, 2, 1, A, 3, B, 3, 2, C, 3);

    for (i = 0; i < 9; i++)
        std::cout << C[i] << " ";

    std::cout << std::endl;
}
*/

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
