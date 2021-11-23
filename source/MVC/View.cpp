#include "View.h"
#include <cstdio>
#include <imgui.h>
#include <backends/imgui_impl_opengl3.h>
#include <backends/imgui_impl_glfw.h>
#include <implot.h>

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
	glfwWindowHint(GLFW_SAMPLES, 4);


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

	glEnable(GL_MULTISAMPLE);

	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();

	// Setup Platform/Renderer backends
	ImGui_ImplGlfw_InitForOpenGL(thiz->mGLFWWindow, true);
	ImGui_ImplOpenGL3_Init(glsl_version);

	ImPlotContext* implot_ctx = ImPlot::CreateContext();
	if (implot_ctx == nullptr)
	{
		fprintf(stderr, "Failed to initialize ImPlot!\n");
		return;
	}
	ImPlot::SetCurrentContext(implot_ctx);


	if (glfwRawMouseMotionSupported())
		glfwSetInputMode(mGLFWWindow, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);

	glfwSetKeyCallback(mGLFWWindow, keyCallback);
	glfwSetCursorPosCallback(mGLFWWindow, mouseMoveCallback);
	glfwSetMouseButtonCallback(mGLFWWindow, mouseButtonCallback);
	glfwSetScrollCallback(mGLFWWindow, mouseScrollCallback);
	glfwSetFramebufferSizeCallback(mGLFWWindow, framebufferSizeCallback);

	ImGuiStyle& style = ImGui::GetStyle();

	style.FrameRounding = 0.f;
	style.FramePadding = ImVec2(2.f, 2.f);
	style.FrameBorderSize = 1.f;
	style.WindowBorderSize = 1.f;
	style.GrabRounding = 20.f;
	style.GrabMinSize = 18.f;
	style.WindowRounding = 0.f;
	style.DisplayWindowPadding = ImVec2(2.f, 2.f);
	style.WindowPadding = ImVec2(2.f, 2.f);
	style.ItemInnerSpacing = ImVec2(4.f, 4.f);


	/*float active_col_white[3] = {0.8f, 0.8f, 0.8f};
	float hover_col_white[3] = { 0.7f, 0.7f, 0.7f };
	float default_col_white[3] = { 0.6f, 0.6f, 0.6f };

	float default_col[3] = { 66.f / 255.f, 68.f / 255.f, 69.f / 255.f };
	float hover_col[3] = { 56.f / 255.f, 58.f / 255.f, 59.f / 255.f };
	float active_col[3] = { 46.f / 255.f, 48.f / 255.f, 49.f / 255.f };

	style.Colors[ImGuiCol_WindowBg] = ImVec4(0.25f, 0.25f, 0.25f, 0.8f);
	style.Colors[ImGuiCol_TitleBg] = ImVec4(default_col[0], default_col[1], default_col[2], 1.f);
	style.Colors[ImGuiCol_TitleBgActive] = ImVec4(active_col[0], active_col[1], active_col[2], 1.f);
	style.Colors[ImGuiCol_SliderGrab] = ImVec4(default_col[0], default_col[1], default_col[2], 1.f);
	style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(active_col[0], active_col[1], active_col[2], 1.f);
	style.Colors[ImGuiCol_Header] = ImVec4(default_col[0], default_col[1], default_col[2], 1.f);
	style.Colors[ImGuiCol_HeaderHovered] = ImVec4(hover_col[0], hover_col[1], hover_col[2], 1.f);
	style.Colors[ImGuiCol_HeaderActive] = ImVec4(active_col[0], active_col[1], active_col[2], 1.f);
	style.Colors[ImGuiCol_FrameBg] = ImVec4(active_col_white[0], active_col_white[1], active_col_white[2], 0.16f);
	style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(active_col_white[0], active_col_white[1], active_col_white[2], 0.32f);
	style.Colors[ImGuiCol_FrameBgActive] = ImVec4(active_col_white[0], active_col_white[1], active_col_white[2], 0.48f);
	style.Colors[ImGuiCol_CheckMark] = ImVec4(active_col_white[0], active_col_white[1], active_col_white[2], 1.0f);
	style.Colors[ImGuiCol_Tab] = ImVec4(default_col[0], default_col[1], default_col[2], 0.5f);
	style.Colors[ImGuiCol_TabHovered] = ImVec4(hover_col[0], hover_col[1], hover_col[2], 1.0f);
	style.Colors[ImGuiCol_TabActive] = ImVec4(active_col[0], active_col[1], active_col[2], 1.0f);
	style.Colors[ImGuiCol_ResizeGrip] = ImVec4(active_col[0], active_col[1], active_col[2], 0.2f);
	style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(active_col[0], active_col[1], active_col[2], 0.4f);
	style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(active_col[0], active_col[1], active_col[2], 0.6f);
	style.Colors[ImGuiCol_Separator] = ImVec4(active_col[0], active_col[1], active_col[2], 0.6f);
	style.Colors[ImGuiCol_Button] = ImVec4(default_col[0], default_col[1], default_col[2], 1.0f);
	style.Colors[ImGuiCol_ButtonHovered] = ImVec4(active_col_white[0], active_col_white[1], active_col_white[2], 0.6f);
	style.Colors[ImGuiCol_ButtonActive] = ImVec4(active_col_white[0], active_col_white[1], active_col_white[2], 1.0f);
	style.Colors[ImGuiCol_Text] = ImVec4(1.f, 1.f, 1.f, 1.f);*/
}

void View::Destroy()
{
	if (mGLFWWindow != nullptr)
	{
		glfwDestroyWindow(mGLFWWindow);
		glfwTerminate();
	}

	mThread.join();
}

void View::OnInitialize(Model* model)
{
	mModel = model;
	//std::thread thread;

	mThread = std::thread(&Model::Train, mModel);
	

	//mModel->Train();

	glViewport(0, 0, mWidth, mHeight);
	glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
}

void View::OnUpdate()
{
	glfwPollEvents();

	glClear(GL_COLOR_BUFFER_BIT);

	// Start the Dear ImGui frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	//static bool show_demo_window = true;
	ImGui::ShowDemoWindow();

	ImPlot::ShowDemoWindow();

	ImGui::SetNextWindowSize(ImVec2(500.f, 400.f), ImGuiCond_FirstUseEver);
	ImGui::Begin("Data", nullptr);
	{
		//ImGui::PlotLines("value", )
		std::vector<float>& values = mModel->GetValues();
		std::vector<float>& gradients = mModel->GetGradients();

		
		
		static ImPlotAxisFlags flags = ImPlotAxisFlags_AutoFit;
		
		if (ImPlot::BeginPlot("##values", NULL, NULL, ImVec2(-1, 500.f), 0, flags, flags)) 
		{
			
			ImPlot::PlotLine("val", values.data(), values.size());
			ImPlot::PlotLine("grad", gradients.data(), gradients.size());
			
			ImPlot::EndPlot();
		}
	}
	ImGui::End();


	if (ImGui::Begin("##draw", NULL))
	{

		static float values1[28][28] = {};
		static bool is_fiiled = false;
		if (!is_fiiled)
		{
			for (int i = 0; i < 28; i++)
			{
				for (int j = 0; j < 28; j++)
				{
					values1[i][j] = std::rand() % 101 / 100.f;
				}
			}
			is_fiiled = true;
		}
		

		static float scale_min = 0;
		static float scale_max = 6.3f;

		static ImPlotColormap map = ImPlotColormap_Viridis;
		static ImPlotAxisFlags axes_flags = ImPlotAxisFlags_Lock;
		if (ImPlot::BeginPlot("##Heatmap1", NULL, NULL, ImVec2(800, 800), ImPlotFlags_NoLegend | ImPlotFlags_NoMousePos, axes_flags, axes_flags)) 
		{

			ImPlot::PushColormap(map);
			ImVec2 left_top = ImGui::GetCursorPos();
			ImPlot::PlotHeatmap("heat", values1[0], 28, 28);


			ImVec4 colf_y = ImVec4(0.f, 1.f, 0.f, 1.0f);
			const ImU32 col_unreaded = ImColor(colf_y);

			double xpos, ypos;
			glfwGetCursorPos(mGLFWWindow, &xpos, &ypos);

			ImVec2 general_pos = ImVec2(xpos, ypos); // ImGui::GetCursorScreenPos();

			ImDrawList* draw_list = ImGui::GetWindowDrawList();
			draw_list->AddCircleFilled(general_pos, 10.f, col_unreaded);

			draw_list->AddCircleFilled(left_top, 20.f, col_unreaded);

			ImPlot::EndPlot();
		}
	}
	ImGui::End();


	// Rendering
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	glfwSwapBuffers(mGLFWWindow);
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
	glViewport(0, 0, mWidth, mHeight);
}

