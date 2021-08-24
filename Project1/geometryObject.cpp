#include "geometryObject.h"
#include "imgui/imgui.h"
geometryObject::geometryObject() {

}
geometryObject::~geometryObject() {

}

void geometryObject::objectShow() {
	if (ImGui::TreeNode(m_name.c_str())) {
		for (int i = 0; i < m_materialObjects.size(); i++) {
			m_materialObjects[i]->objectShow();
		}
		ImGui::TreePop();
	}
	
}