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


	/*ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(5.f, 5.f));
	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 10.f);
	ImGui::Begin("Gradient");
	{
		ImVec2 p0 = ImGui::GetWindowPos();
		ImVec2 p1 = ImVec2(p0.x + ImGui::GetWindowSize().x, p0.y + ImGui::GetWindowSize().y);
		ImU32 col_a = ImGui::GetColorU32(IM_COL32(0, 0, 0, 255));
		ImU32 col_b = ImGui::GetColorU32(IM_COL32(255, 255, 255, 255));

		ImDrawList* draw_list = ImGui::GetWindowDrawList(); //ImGui::GetBackgroundDrawList();
		draw_list->AddRectFilledMultiColor(p0, p1, col_a, col_a, col_b, col_b);

	}
	ImGui::End();
	ImGui::PopStyleVar(2);*/
	



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

	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.f, 0.f));
	if (ImGui::Begin("##draw", NULL, ImGuiWindowFlags_NoTitleBar))
	{
		//ImGui::Image((ImTextureID)mCanvas.GetGLTexID(), ImVec2(100.f, 100.f));
		static float values1[28][28] = {};
		

		static float scale_min = 0;
		static float scale_max = 6.3f;

		static ImPlotColormap map = ImPlotColormap_Viridis;
		static ImPlotAxisFlags axes_flags = ImPlotAxisFlags_Lock | ImPlotAxisFlags_NoDecorations;
		ImPlot::PushStyleVar(ImPlotStyleVar_PlotPadding, ImVec2(0.f, 0.f));
		float size = 800.f;
		ImVec2 tab_size = ImVec2(size, size);
		ImVec2 left_top = ImGui::GetCursorPos();
		left_top.x = ImGui::GetWindowPos().x;
		left_top.y = ImGui::GetWindowPos().y;
		const int16_t rows = 28, cols = 28;
		float cell_size = size / cols;
		if (ImPlot::BeginPlot("##Heatmap1", NULL, NULL, tab_size, ImPlotFlags_CanvasOnly, axes_flags, axes_flags))
		{
			
			ImPlot::PushColormap(map);
			//ImVec2 left_top = ImVec2(ImGui::GetCursorPos().x + ImGui::GetWindowPos().x, ImGui::GetCursorPos().y + ImGui::GetWindowPos().y);
			ImPlot::PlotHeatmap("heat", values1[0], rows, cols);
			

			ImVec4 colf_y = ImVec4(0.8f, 0.8f, 0.f, 1.f);
			const ImU32 col_unreaded = ImColor(colf_y);

			double xpos, ypos;
			glfwGetCursorPos(mGLFWWindow, &xpos, &ypos);
			int state = glfwGetMouseButton(mGLFWWindow, GLFW_MOUSE_BUTTON_LEFT);
			const float R = 40.f;
			if (state == GLFW_PRESS && ImGui::IsItemHovered())
			{				
				for (int i = 0; i < 28; i++)
				{
					for (int j = 0; j < 28; j++)
					{
						ImVec4 colf_y = ImVec4(0.f, 1.f, 0.f, 0.5f);
						const ImU32 col_unreaded = ImColor(colf_y);
						ImVec2 cell_point;
						cell_point.x = left_top.x + j * cell_size + cell_size / 2.f;
						cell_point.y = left_top.y + i * cell_size + cell_size / 2.f;

						float d_x = xpos - cell_point.x;
						float d_y = ypos - cell_point.y;

						float radius = std::sqrt(d_x * d_x + d_y * d_y);
						radius = radius / (R + 10.f);

						float new_val;
						if (radius >= 0.f)
							new_val = 1.f / (1.f + std::pow(M_E, 7.f * (radius - 0.5f)));
						else
							new_val = 0.f;

						if (new_val > 1.f)
							new_val = 1.f;

						if (radius > 0.f && new_val <= 1 && values1[i][j] < new_val)
						{
							values1[i][j] = new_val;
						}
							
						if (radius > 1.f)
						{
							int a = 0;
						}
					}
				}
			}




			ImVec2 general_pos = ImVec2(xpos, ypos); // ImGui::GetCursorScreenPos();

			ImDrawList* draw_list = ImGui::GetWindowDrawList();
			draw_list->AddCircleFilled(general_pos, R, col_unreaded);

			//draw_list->AddCircleFilled(left_top, 20.f, col_unreaded);

			ImPlot::EndPlot();
		}
		ImPlot::PopStyleVar();

		if (ImGui::Button("Clear", ImVec2(80.f, 20.f)))
		{
			for (int i = 0; i < 28; i++)
			{
				for (int j = 0; j < 28; j++)
				{
					values1[i][j] = 0.f;
				}
			}
		}
		ImGui::SameLine();
		static double val = -1;
		if (ImGui::Button("Eval", ImVec2(80.f, 20.f)))
		{
			val = mModel->Predict(values1);
		}
		ImGui::Text(std::to_string(val).c_str());

	}
	ImGui::End();
	ImGui::PopStyleVar();




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

