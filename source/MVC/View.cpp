#include "View.h"
#include <cstdio>

static View* thiz = nullptr;

//glfw callbacks
static void glfwErrorCallback(int error, const char* description)
{
	fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}
static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (thiz)
	{
		if (action == GLFW_PRESS)
			thiz->OnKeyPress(key);
		if (action == GLFW_REPEAT)
			thiz->OnKeyRepeat(key);
		if (action == GLFW_RELEASE)
			thiz->OnKeyRelease(key);
	}
}
static void mouseMoveCallback(GLFWwindow* window, double xpos, double ypos)
{
	if (thiz)
	{
		thiz->OnMouseMove(xpos, ypos);
	}
}
static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	if (thiz)
	{
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);

		if (action == GLFW_PRESS)
		{
			if (button == GLFW_MOUSE_BUTTON_LEFT)
			{
				thiz->OnMouseLeftDown(xpos, ypos);
			}
			else if (button == GLFW_MOUSE_BUTTON_RIGHT)
			{
				thiz->OnMouseRightDown(xpos, ypos);
			}
			else if (button == GLFW_MOUSE_BUTTON_MIDDLE)
			{
				thiz->OnMouseMiddleDown(xpos, ypos);
			}
		}
		else if (action == GLFW_RELEASE)
		{
			if (button == GLFW_MOUSE_BUTTON_LEFT)
			{
				thiz->OnMouseLeftUp(xpos, ypos);
			}
			else if (button == GLFW_MOUSE_BUTTON_RIGHT)
			{
				thiz->OnMouseRightUp(xpos, ypos);
			}
			else if (button == GLFW_MOUSE_BUTTON_MIDDLE)
			{
				thiz->OnMouseMiddleUp(xpos, ypos);
			}
		}
	}
}
static void mouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	if(thiz)
		thiz->OnMouseWhell(yoffset);
}
static void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	if(thiz)
		thiz->OnResize(width, height);
}


View::View() {}
View::~View() {}

void View::Create(unsigned int width, unsigned int height, const char* title)
{
	thiz = this;

	glfwSetErrorCallback(glfwErrorCallback);

	mWidth = width;
	mHeight = height;

	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW library!\n");
		return;
	}

	const char* glsl_version = "#version 330";
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	mGLFWWindow = glfwCreateWindow(mWidth, mHeight, title, nullptr, nullptr);

	if (mGLFWWindow == nullptr)
	{
		fprintf(stderr, "Failed to create GLFW window!\n");
		return;
	}

	glfwMakeContextCurrent(mGLFWWindow);
	glfwSwapInterval(1);

	if (gladLoadGL() == NULL)
	{
		fprintf(stderr, "Failed to initialize OpenGL loader!\n");
		return;
	}

	//mGUI.Init(glsl_version);

	if (glfwRawMouseMotionSupported())
		glfwSetInputMode(mGLFWWindow, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);

	glfwSetKeyCallback(mGLFWWindow, keyCallback);
	glfwSetCursorPosCallback(mGLFWWindow, mouseMoveCallback);
	glfwSetMouseButtonCallback(mGLFWWindow, mouseButtonCallback);
	glfwSetScrollCallback(mGLFWWindow, mouseScrollCallback);
	glfwSetFramebufferSizeCallback(mGLFWWindow, framebufferSizeCallback);
}
void View::Destroy()
{

}

void View::OnInitialize()
{
    
}
void View::OnUpdate()
{
    
}
void View::OnFinalize()
{

}

void View::OnMouseLeftDown(double x, double y)
{
}
void View::OnMouseLeftUp(double x, double y)
{
}
void View::OnMouseRightDown(double x, double y)
{
}
void View::OnMouseRightUp(double x, double y)
{
}
void View::OnMouseMiddleDown(double x, double y)
{
}
void View::OnMouseMiddleUp(double x, double y)
{
}
void View::OnMouseMove(double x, double y)
{

}
void View::OnMouseWhell(double offset)
{
}

void View::OnKeyPress(int key)
{
}
void View::OnKeyRepeat(int key)
{
}
void View::OnKeyRelease(int key)
{
}

void View::OnResize(int width, int height)
{
    
}