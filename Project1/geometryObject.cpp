#include "geometryObject.h"
#include "materialObject.h"
#include "imgui/imgui.h"
geometryObject::geometryObject() {

}
geometryObject::~geometryObject() {

}

void geometryObject::objectShow() {
	if (ImGui::TreeNode(m_name.c_str())) {
		for (int i = 0; i < m_materialObjects.size(); i++) {
			m_materialObjects[i]->asTObject<materialObject>()->objectShow();
		}
		ImGui::TreePop();
	}
	
}

void geometryObject::clearMaterialShowFlag() {
	for (auto e : m_materialObjects) {
		e->asTObject<materialObject>()->clearShow();
	}
}