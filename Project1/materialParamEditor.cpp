#include "materialParamEditor.h"
#include "materialShaderParamEnum.h"
#include "SoulEditorRender.hpp"
#include "imgui/imgui.h"
#include <windows.h>
#include <fstream>
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
	jointer = std::make_shared<shaderJointer>();
}

materialParamEditor::~materialParamEditor() {

}

void materialParamEditor::findDefaultMap() {
	auto diffuseDefaultPath = m_resoucePath + m_name + "_diffuseMap.png";
	std::ifstream File(diffuseDefaultPath);
	if (File.is_open()) {
		strcpy(p.BRDF.diffuseMap, std::string(m_name + "_diffuseMap.png").c_str());
	}
	File.close();

	auto normalDefaultPath = m_resoucePath + m_name + "_normalMap.png";
	File.open(normalDefaultPath);
	if (File.is_open()) {
		strcpy(p.BRDF.normalMap, std::string(m_name + "_normalMap.png").c_str());
	}
	File.close();

	auto mraDefaultPath = m_resoucePath + m_name + "_mraMap.png";
	File.open(mraDefaultPath);
	if (File.is_open()) {
		strcpy(p.BRDF.mraMap, std::string(m_name + "_mraMap.png").c_str());
	}
	File.close();
}

void materialParamEditor::setDefaultParam() {
	editorRender* render = editorRender::getRender();
	render->setPbrParam("roughnessParam", p.BRDF.roughness, m_name);
	render->setPbrParam("matallicParam", p.BRDF.matallic, m_name);
	render->setPbrParam("fresnelF0", p.BRDF.fresnelF0, m_name);
	render->setPbrParamMap("diffuseMap", m_resoucePath + p.BRDF.diffuseMap, m_name);
	render->setPbrParamMap("normalMap", m_resoucePath + p.BRDF.normalMap, m_name);
	render->setPbrParamMap("mraMap", m_resoucePath + p.BRDF.mraMap, m_name);
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
			render->setPbrParam("fresnelF0", p.BRDF.fresnelF0, m_name);
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

	if (ImGui::TreeNode("Specular")) {
		const char* specularType = SPECULAR_TYPE_NAME[specularTypeIndex];
		if (ImGui::BeginCombo("SpecularList", specularType))
		{
			for (int n = 0; n < IM_ARRAYSIZE(SPECULAR_TYPE_NAME); n++)
			{
				const bool is_selected = (specularTypeIndex == n);
				if (ImGui::Selectable(SPECULAR_TYPE_NAME[n], is_selected)) {
					specularTypeIndex = n; 
					addSpecularShader();
				}

				if (is_selected)
					ImGui::SetItemDefaultFocus();
			}
			ImGui::EndCombo();
		}
		showSpecular(specularTypeIndex);
		ImGui::TreePop();
	}

	if (ImGui::TreeNode("clearCoat")) {
		const char* clearCoatType = CLEARCOAT_TYPE_NAME[clearCoatTypeIndex];
		if (ImGui::BeginCombo("clearCoatList", clearCoatType))
		{
			for (int n = 0; n < IM_ARRAYSIZE(CLEARCOAT_TYPE_NAME); n++)
			{
				const bool is_selected = (clearCoatTypeIndex == n);
				if (ImGui::Selectable(CLEARCOAT_TYPE_NAME[n], is_selected)) {
					clearCoatTypeIndex = n;
					addClearCoatShader();
				}
				//TODO: shader
				// Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
				if (is_selected)
					ImGui::SetItemDefaultFocus();
			}
			ImGui::EndCombo();
		}
		showClearCoat(clearCoatTypeIndex);
		ImGui::TreePop();
	}

	if (ImGui::TreeNode("sss")) {
		const char* subsurfaceType = SUBSURFACE_TYPE_NAME[subsurfaceTypeIndex];
		if (ImGui::BeginCombo("sssList", subsurfaceType))
		{
			for (int n = 0; n < IM_ARRAYSIZE(SUBSURFACE_TYPE_NAME); n++)
			{
				const bool is_selected = (subsurfaceTypeIndex == n);
				if (ImGui::Selectable(SUBSURFACE_TYPE_NAME[n], is_selected))
					subsurfaceTypeIndex = n;
				    jointer->addHeader(subsurfaceType);
				    jointer->addMicroDefine("SUBSURFACE");
				// Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
				if (is_selected)
					ImGui::SetItemDefaultFocus();
			}
			ImGui::EndCombo();
		}
		ImGui::TreePop();
	}
	ImGui::End();
}

void materialParamEditor::showSpecular(int specularIndex) {
	editorRender* render = editorRender::getRender();
	if (specularIndex == 2) {
		if (ImGui::SliderFloat("anisotropy", &p.anisotropic.anisotropic, -1.0f, 1.0f)) {
			render->setPbrParam("anisotropy", p.anisotropic.anisotropic, m_name);
		}; 
		ImGui::InputText("directionMap", p.anisotropic.directionMap, 64); ImGui::SameLine();
		if (ImGui::Button("import mra")) {
			render->setPbrParamMap("directionMap", m_resoucePath + p.anisotropic.directionMap, m_name);
		}
	}
}

void materialParamEditor::showClearCoat(int clearCoatIndex) {
	editorRender* render = editorRender::getRender();
	if (clearCoatIndex == 1) {
		if (ImGui::SliderFloat("clearCoatPower", &p.clearCoat.clearCoat, 0.0f, 1.0f)) {
			render->setPbrParam("clearCoatPower", p.clearCoat.clearCoat, m_name);
		};
		if (ImGui::SliderFloat("clearCoatRoughness", &p.clearCoat.clearCoatRoughness, 0.0f, 1.0f)) {
			render->setPbrParam("clearCoatRoughness", p.clearCoat.clearCoatRoughness, m_name);
		};
		if (ImGui::ColorEdit3("clearCoatColor", (float*)&p.clearCoat.clearCoatColor)) {
			render->setPbrParam("clearCoatColor", glm::vec3(p.clearCoat.clearCoatColor.x, p.clearCoat.clearCoatColor.y, p.clearCoat.clearCoatColor.z ), m_name);
		} 
	}
}

void materialParamEditor::addClearCoatShader() {
	const char* clearCoatType = CLEARCOAT_TYPE_NAME[clearCoatTypeIndex];

	for (int n = 0; n < IM_ARRAYSIZE(CLEARCOAT_TYPE_NAME); n++) {
		if (clearCoatTypeIndex == n) {
			if (clearCoatType == "clearCoat") {
				jointer->addHeader("clearCoat");
				jointer->addMicroDefine("CLEARCOAT");
			} else {
				jointer->deleteHeader("clearCoat");
				jointer->deleteMicroDefine("CLEARCOAT");
			}
			//if (clearCoatType != "None") {
			//	jointer->addHeader(clearCoatType);
			//	jointer->addMicroDefine("CLEARCOAT");
			//} else {
			//	jointer->deleteMicroDefine("CLEARCOAT");
			//}
		}
	}
	jointer->jointShader();
	editorRender* render = editorRender::getRender();
	render->setProgram(m_name, m_name, jointer->getVert(), jointer->getFrag());
}

void materialParamEditor::addSpecularShader() {
	const char* specularType = SPECULAR_TYPE_NAME[specularTypeIndex];

	for (int n = 0; n < IM_ARRAYSIZE(SPECULAR_TYPE_NAME); n++) {
		if (specularTypeIndex == n) {
			if (specularType == "Anisotropic") {
				jointer->addHeader("Anisotropic");
				jointer->addMicroDefine("ANISOTROPIC");
			}
			else {
				jointer->deleteHeader("Anisotropic");
				jointer->deleteMicroDefine("ANISOTROPIC");
			}
			//if (clearCoatType != "None") {
			//	jointer->addHeader(clearCoatType);
			//	jointer->addMicroDefine("CLEARCOAT");
			//} else {
			//	jointer->deleteMicroDefine("CLEARCOAT");
			//}
		}
	}
	jointer->jointShader();
	editorRender* render = editorRender::getRender();
	render->setProgram(m_name, m_name, jointer->getVert(), jointer->getFrag());
}

//TODO: s
//void addSubsurfaceShader(std::string type);
//void showSubsurface(int SubsurfaceIndex);