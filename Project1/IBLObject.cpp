#include "IBLObject.h"
#include "SoulEditorRender.hpp"
#include "imgui/imgui.h"

#include <windows.h>
using namespace Soul;

IBLObject::IBLObject() {

	char buf[1000];
	GetCurrentDirectory(1000, buf); //得到当前工作路径
	m_resoucePath = std::string(buf) + "\\resource\\";

	for (int i = 0; i < m_resoucePath.length(); i++) {
		if (m_resoucePath[i] == '\\') {
			m_resoucePath[i] = '/';
		}
	}
}

IBLObject::~IBLObject() {

}

void IBLObject::objectShow() {
	editorRender* render = editorRender::getRender();
	if (ImGui::TreeNode("IBL")) {
		ImGui::InputText("HDRimage", IBLFolder, 64); ImGui::SameLine();
		if (ImGui::Button("import HDRimage")) {
			render->setIBL(m_resoucePath + IBLFolder);
		}
		ImGui::TreePop();
	}
}

