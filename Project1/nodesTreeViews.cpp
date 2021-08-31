#include "nodesTreeViews.h"
#include "materialObject.h"
#include "lightObject.h"
#include "SoulEditorRender.hpp"
#include <windows.h>
#include <iostream>

nodesTreeViews::nodesTreeViews() {
	char buf[1000];
	GetCurrentDirectory(1000, buf); //得到当前工作路径
	m_resoucePath = std::string(buf) + "\\resource\\";

	for (int i = 0; i < m_resoucePath.length(); i++) {
		if (m_resoucePath[i] == '\\') {
			m_resoucePath[i] = '/';
		}
	}
	reader = std::make_shared<fbxReader>(m_resoucePath);

	m_geometry = std::make_shared<geometryObject>();
	m_light0 = std::make_shared<lightObject>();
	m_light0->setName("light0");
	m_light1 = std::make_shared<lightObject>();
	m_light1->setName("light1");
	m_light1->setLightNum(1);
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
	m_light0->objectShow();
	m_light1->objectShow();
	if (hasGeometry) m_geometry->asTObject<geometryObject>()->objectShow();
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

	if (!ImGui::Begin("fbx importer", &showFbxFilter))//could set window flags in second param
	{
		// Early out if the window is collapsed, as an optimization.
		ImGui::End();
		return;
	}

	static ImGuiTextFilter filter("expression.fbx");
	filter.Draw();
	if (ImGui::Button("Import")) {
		char* fileName;
		fileName = filter.InputBuf;
		reader->setFileName(fileName);
		reader->read();
		refreshNodes(reader);
		m_geometry->setName(fileName);
		hasGeometry = true;
	}
	ImGui::End();
}

void nodesTreeViews::refreshNodes(std::shared_ptr<fbxReader> reader) {
	auto meshs = reader->getMeshes();
	Soul::editorRender* render = Soul::editorRender::getRender();
	render->addGroup(meshs);
	for (auto e : meshs) {
		auto mesh = std::make_shared<FbxMesh>(e);
		materialObject::Ptr material = std::make_shared<materialObject>();
		material->setMesh(mesh);
		m_geometry->addObject(material);
		material->setFatherGeometry(m_geometry);
		render->setProgram(mesh->name, mesh->name, m_resoucePath + "defaultBrdf.vert", m_resoucePath + "defaultBrdf.frag", 1);
	}
}
