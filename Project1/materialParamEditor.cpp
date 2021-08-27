#include "materialParamEditor.h"
#include "imgui/imgui.h"

materialParamEditor::materialParamEditor() {

}
materialParamEditor::~materialParamEditor() {

}

void materialParamEditor::showParamView() {
	const char* title = m_name.c_str();
	if (!ImGui::Begin(title, &showParamViewFlag))//could set window flags in second param
	{//
		// Early out if the window is collapsed, as an optimization.
		ImGui::End();
		return;
	}
	if (ImGui::TreeNode("PBR")) {
		if (ImGui::SliderFloat("roughness", &p.BRDF.roughness, 0.0f, 1.0f)) {
			ImGui::SliderFloat("matallc", &p.BRDF.matallic, 0.0f, 1.0f);
		}
		ImGui::SliderFloat("matallic", &p.BRDF.matallic, 0.0f, 1.0f);
		ImGui::SliderFloat("fresnel", &p.BRDF.fresnelF0, 0.0f, 1.0f);
		ImGui::TreePop();
	}
	ImGui::End();
}