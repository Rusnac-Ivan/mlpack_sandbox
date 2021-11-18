#ifndef _APPLICATION_H_
#define _APPLICATION_H_

#include "../MVC/View.h"
#include "../MVC/Controller.h"
#include "../MVC/Model.h"

class Application
{
        View mView;
        //Controller mController;
        Model mModel;
    private:
        Application(unsigned int width, unsigned int height, const char* title);
        Application(const Application&) = delete;
        Application& operator=(Application&) = delete;
    public:
        static Application& Run(unsigned int width, unsigned int height, const char* title);
    private:
        void MainLoop();
};


#endif // !_APPLICATION_H_


