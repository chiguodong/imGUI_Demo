
#include <imgui/imgui.h>
#include "materialObject.h"
#include "geometryObject.h"
#include "materialEditorManager.h"

materialObject::materialObject() {
	auto maneger = materialEditorManager::getManager();
	m_editorView = std::make_shared<materialParamEditor>();
	maneger->addParamEditor(m_editorView);
}

materialObject::~materialObject() {

}

void materialObject::objectShow() {
	if (ImGui::Selectable(m_name.c_str(), &m_editorView->showParamViewFlag)) {
		m_geometry->asTObject<geometryObject>()->clearMaterialShowFlag();
		m_editorView->showParamViewFlag = true;
	}
}

void materialObject::setMesh(std::shared_ptr<FbxMesh> mesh) {
	m_mesh = mesh;
	m_name = mesh->name;
	m_editorView->setName(m_name);
	m_editorView->init();
}
