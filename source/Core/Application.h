#ifndef _APPLICATION_H_
#define _APPLICATION_H_

class Application
{
    private:
        Application() {};
        Application(const Application&) = delete;
        Application& operator=(Application&) = delete;
    public:
        static Application& Run(int argc, const char** argv, const char* version, const char* title);
    private:
        void MainLoop();
};


#endif // !_APPLICATION_H_


