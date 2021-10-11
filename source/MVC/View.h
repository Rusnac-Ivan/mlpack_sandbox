#ifndef _VIEW_H_
#define _VIEW_H_

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class View
{
        class GUI
        {
            public:
                GUI() {}
                ~GUI() {}

                void Init(const char* glsl_version);
                void Render();

            private:
                void DrawElements();
        };

    private:
        unsigned int mWidth;
        unsigned int mHeight;
        GLFWwindow* mGLFWWindow;
        GUI mGUI;
    public:
        View();
        ~View();

        bool WindowIsOpen() { return !glfwWindowShouldClose(mGLFWWindow); }

        void Create(unsigned int width, unsigned int height, const char* title);
        void Destroy();

        void OnInitialize();
        void OnUpdate();
        void OnFinalize();

        void OnMouseLeftDown(double x, double y);
        void OnMouseLeftUp(double x, double y);
        void OnMouseRightDown(double x, double y);
        void OnMouseRightUp(double x, double y);
        void OnMouseMiddleDown(double x, double y);
        void OnMouseMiddleUp(double x, double y);
        void OnMouseMove(double x, double y);
        void OnMouseWhell(double offset);

        void OnKeyPress(int key);
        void OnKeyRepeat(int key);
        void OnKeyRelease(int key);

        void OnResize(int width, int height);


};



#endif