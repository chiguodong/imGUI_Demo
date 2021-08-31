#include "lightObject.h"

lightObject::lightObject() {
	lightEditorManager* lightManager = lightEditorManager::getManager();
	m_editorView = std::make_shared<lightParamEditor>();
	lightManager->addLight(m_editorView);
	//m_editorView->setDefaultParam();
}

lightObject::~lightObject() {

}

void lightObject::objectShow() {
	if (ImGui::Selectable(m_name.c_str(), &m_editorView->showParamViewFlag)) { 
		m_editorView->showParamViewFlag = true;
	}
}