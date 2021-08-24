#include "nodesTreeViews.h"

#include <windows.h>
#include <iostream>

nodesTreeViews::nodesTreeViews() {
	char buf[1000];
	GetCurrentDirectory(1000, buf); //得到当前工作路径
	std::string resoucePath = buf;
	reader = std::make_shared<fbxReader>(resoucePath + "\\resource\\");
}

nodesTreeViews::~nodesTreeViews() {

}


void nodesTreeViews::showTreeNodes() {
	static bool p_open = true;

	const ImGuiViewport* main_viewport = ImGui::GetMainViewport();
	ImGui::SetNextWindowPos(ImVec2(main_viewport->WorkPos.x + 650, main_viewport->WorkPos.y + 20), ImGuiCond_FirstUseEver);
	ImGui::SetNextWindowSize(ImVec2(550, 680), ImGuiCond_FirstUseEver);

	ImGuiWindowFlags window_flags = ImGuiWindowFlags_None;
	window_flags |= ImGuiWindowFlags_MenuBar;

	if (!ImGui::Begin("nodes list", &p_open, window_flags))//could set window flags in second param
	{
		// Early out if the window is collapsed, as an optimization.
		ImGui::End();
		return;
	}
	ImGui::PushItemWidth(ImGui::GetFontSize() * 0.35f);
	showMenu();
	//for (auto e : m_objects) {
	//	e->objectShow();
	//}
	ImGui::End();

	if (showFbxFilter) showFilter();
}


void nodesTreeViews::showMenu() {
	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("Menu"))
		{
			ImGui::MenuItem("New fbx", NULL, &showFbxFilter);
			ImGui::EndMenu();
		}
		ImGui::EndMenuBar();
	}
}

void nodesTreeViews::showFilter() {
	const ImGuiViewport* main_viewport = ImGui::GetMainViewport();
	ImGui::SetNextWindowPos(ImVec2(main_viewport->WorkPos.x + 650, main_viewport->WorkPos.y + 30), ImGuiCond_FirstUseEver);

	if (!ImGui::Begin("fbx importer"))//could set window flags in second param
	{
		// Early out if the window is collapsed, as an optimization.
		ImGui::End();
		return;
	}

	static ImGuiTextFilter filter;
	filter.Draw();
	if (ImGui::Button("Import")) {
		char* fileName;
		fileName = filter.InputBuf;
		reader->setFileName(fileName);
		reader->read();
	}
	ImGui::End();
}

void nodesTreeViews::refreshNodes() {

}