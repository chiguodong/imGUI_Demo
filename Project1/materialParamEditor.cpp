#include "materialParamEditor.h"
#include "SoulEditorRender.hpp"
#include "imgui/imgui.h"
#include <windows.h>
using namespace Soul;
materialParamEditor::materialParamEditor() {
	char buf[1000];
	GetCurrentDirectory(1000, buf); //得到当前工作路径
	m_resoucePath = std::string(buf) + "\\resource\\";

	for (int i = 0; i < m_resoucePath.length(); i++) {
		if (m_resoucePath[i] == '\\') {
			m_resoucePath[i] = '/';
		}
	}

}
materialParamEditor::~materialParamEditor() {

}

void materialParamEditor::showParamView() {
	editorRender* render = editorRender::getRender();
	const char* title = m_name.c_str();
	if (!ImGui::Begin(title, &showParamViewFlag))//could set window flags in second param
	{//
		// Early out if the window is collapsed, as an optimization.
		ImGui::End();
		return;
	}
	if (ImGui::TreeNode("PBR")) {
		if (ImGui::SliderFloat("roughness", &p.BRDF.roughness, 0.0f, 1.0f)) {
			render->setPbrParam("roughnessParam", p.BRDF.roughness, m_name);
		}
		if (ImGui::SliderFloat("matallic", &p.BRDF.matallic, 0.0f, 1.0f)) {
			render->setPbrParam("matallicParam", p.BRDF.matallic, m_name);
		};
		if (ImGui::SliderFloat("fresnel", &p.BRDF.fresnelF0, 0.0f, 1.0f)) {
			render->setPbrParam("fresnelF0", p.BRDF.matallic, m_name);
		};
		ImGui::InputText("diffuseMap", p.BRDF.diffuseMap, 64); ImGui::SameLine();
		if (ImGui::Button("import diffuse")) {
			render->setPbrParamMap("diffuseMap", m_resoucePath + p.BRDF.diffuseMap, m_name);
		}
		ImGui::InputText("normalMap", p.BRDF.normalMap, 64); ImGui::SameLine();
		if (ImGui::Button("import normal")) {
			render->setPbrParamMap("normalMap", m_resoucePath + p.BRDF.normalMap, m_name);
		}
		ImGui::InputText("mraMap", p.BRDF.mraMap, 64); ImGui::SameLine();
		if (ImGui::Button("import mra")) {
			render->setPbrParamMap("mraMap", m_resoucePath + p.BRDF.mraMap, m_name);
		}

		ImGui::TreePop();
	}
	ImGui::End();
}