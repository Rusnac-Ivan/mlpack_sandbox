#ifndef _APPLICATION_H_
#define _APPLICATION_H_

class Application
{
    private:
        Application();
        Application(const Application&) = delete;
        Application& operator=(Application&) = delete;
    public:
        static Application& Run(unsigned int width, unsigned int height, const char* title);
    private:
        void MainLoop();
};


#endif // !_APPLICATION_H_


