#include "lightParamEditor.h"
#include "imgui/imgui.h"
#include "glm/glm.hpp"


lightParamEditor::lightParamEditor() {
	m_render = editorRender::getRender();
}

lightParamEditor::~lightParamEditor() {

}

void lightParamEditor::setDefaultParam() {
	m_render->setLightParameter("direction", glm::vec3(p.dirLight.direction[0], p.dirLight.direction[1], p.dirLight.direction[2]), lightNum, lightTypeIndex);
	m_render->setLightParameter("position", glm::vec3(p.dirLight.position[0], p.dirLight.position[1], p.dirLight.position[2]), lightNum, lightTypeIndex);
	m_render->setLightParameter("intensity", glm::vec3(p.dirLight.intensity[0], p.dirLight.intensity[1], p.dirLight.intensity[2]), lightNum, lightTypeIndex);
}

void lightParamEditor::showParamView() {
	auto title = std::string("lightParameter") + std::to_string(lightNum);
	const char* lightTitle = title.c_str();
	if (!ImGui::Begin(lightTitle, &showParamViewFlag))//could set window flags in second param
	{//
		// Early out if the window is collapsed, as an optimization.
		ImGui::End();
		return;
	}
	const char* lightType = LIHGT_TYPE[lightTypeIndex];
	if (ImGui::BeginCombo("lightTypeList", lightType)) {
		for (int n = 0; n < IM_ARRAYSIZE(LIHGT_TYPE); n++) {
			const bool is_selected = (lightTypeIndex == n);
			if (ImGui::Selectable(LIHGT_TYPE[n], is_selected)) {
				lightTypeIndex = n; 
			}
		}
		ImGui::EndCombo();
	}
	showLightView();
	ImGui::End();
}

void lightParamEditor::showDirLightView() {
	if (ImGui::SliderFloat3("dirLightDirection", p.dirLight.direction, -3.14f, 3.14f)) {
		m_render->setLightParameter("direction", glm::vec3(p.dirLight.direction[0], p.dirLight.direction[1],p.dirLight.direction[2]), lightNum, lightTypeIndex);
	}
	if (ImGui::SliderFloat3("dirLightPosition", p.dirLight.position, 200.0f, -1000.0f)) {
		m_render->setLightParameter("position", glm::vec3(p.dirLight.position[0], p.dirLight.position[1], p.dirLight.position[2]), lightNum, lightTypeIndex);
	}
	if (ImGui::SliderFloat3("dirLightIntensity", p.dirLight.intensity, 3000.0f, 15000.0f)) {
		m_render->setLightParameter("intensity", glm::vec3(p.dirLight.intensity[0], p.dirLight.intensity[1], p.dirLight.intensity[2]), lightNum, lightTypeIndex);
	}
}

void lightParamEditor::showSpotLightView() {
	if (ImGui::SliderFloat3("spotLightDirection", p.spotLight.direction, 0.0f, 1.0f)) {
		m_render->setLightParameter("direction", glm::vec3(p.spotLight.direction[0], p.dirLight.direction[1], p.dirLight.direction[2]), lightNum, lightTypeIndex);
	}
	if (ImGui::SliderFloat3("spotLightPosition", p.spotLight.position, 0.0f, 1.0f)) {
		m_render->setLightParameter("position", glm::vec3(p.spotLight.position[0], p.dirLight.position[1], p.dirLight.position[2]), lightNum, lightTypeIndex);
	}
	if (ImGui::SliderFloat3("spotLightIntensity", p.spotLight.intensity, 0.0f, 1.0f)) {
		m_render->setLightParameter("intensity", glm::vec3(p.spotLight.intensity[0], p.dirLight.intensity[1], p.dirLight.intensity[2]), lightNum, lightTypeIndex);
	}
	if (ImGui::SliderFloat("spotLightCutoff", &p.spotLight.cutOff, 0.0f, 1.0f)) {
		m_render->setLightParameter("cutOff", p.spotLight.cutOff, lightNum, lightTypeIndex);
	}
	if (ImGui::SliderFloat("spotLightOuterCutOff", &p.spotLight.outerCutOff, 0.0f, 1.0f)) {
		m_render->setLightParameter("outerCutOff", p.spotLight.outerCutOff, lightNum, lightTypeIndex);
	}
}

void lightParamEditor::showPointLightView() { 
	ImGui::SliderFloat3("pointLightPosition", p.pointLight.position, 0.0f, 1.0f);
	ImGui::SliderFloat3("pointLightIntensity", p.pointLight.intensity, 0.0f, 1.0f);
}

void lightParamEditor::showLightView() {
	switch (lightTypeIndex) {
		case 0: {
			showDirLightView();
			break;
		}
		case 1: {
			showSpotLightView();
			break;
		}
		case 2: {
			showPointLightView();
			break;
		}
		default:break;
	}
}