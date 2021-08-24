
#include <imgui/imgui.h>
#include "materialObject.h"

materialObject::materialObject() {

}

materialObject::~materialObject() {

}

void materialObject::objectShow() {
	if (ImGui::TreeNode(m_name.c_str())) {
		if (ImGui::IsItemClicked()) {
			ImGui::Text("lalala lalala");
		}
		ImGui::TreePop();
	}
}

void materialObject::setMesh(std::shared_ptr<FbxMesh> mesh) {
	m_mesh = mesh;
	m_name = mesh->name;
}