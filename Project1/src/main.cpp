#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "nodesTreeViews.h"
#include "materialObject.h"
#include "fbxReader.h"
#include "materialEditorManager.h"
#include "SoulEditorRender.hpp"

using namespace Soul;

int main(void)
{
	GLFWwindow* window;
	/* Initialize the library */
	if (!glfwInit())
		return -1;
	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate(); 
		return -1;
	}
	// GL 3.0 + GLSL 130
	const char* glsl_version = "#version 130";
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	bool err = gladLoadGL() != 0;
	// Imgui context
	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsClassic();

	// Setup Platform/Renderer backends
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init(glsl_version);

	//treeView
	nodesTreeViews treeView;
	//paramView
	auto paramView = materialEditorManager::getManager();
	//3D render
	editorRender* render = editorRender::getRender();
	render->initBlankRender(640, 480);
	//materialObject::Ptr demoMaterialObject = std::make_shared<materialObject>();
	//demoMaterialObject->setName("head");
	//treeView.addObject(demoMaterialObject);

	//fbx reader

//	fbxReader reader("D:/resource/expression.fbx");
//	reader.read();

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Poll for and process events */
		glfwPollEvents();
		//imgui init
		// Start the Dear ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		//tree window
		treeView.showTreeNodes();
		paramView->show();
		ImGui::Render();
		int display_w, display_h;
		glfwGetFramebufferSize(window, &display_w, &display_h);
		glViewport(0, 0, display_w, display_h);

		glClearColor(255, 255, 0, 255);
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);
		render->render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		/* Swap front and back buffers */
		glfwSwapBuffers(window);

	}

	glfwTerminate();
	return 0;
}