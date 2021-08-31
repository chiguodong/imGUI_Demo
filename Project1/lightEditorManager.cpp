#include "lightEditorManager.h"

lightEditorManager::lightEditorManager() {

}

lightEditorManager::~lightEditorManager() {

}

lightEditorManager* lightEditorManager::getManager() {
	static lightEditorManager lightManager;
	return &lightManager;
}

void lightEditorManager::showObject() {
	for (int i = 0; i < m_lights.size(); i++) { 
		if (m_lights[i]->showParamViewFlag) {
			m_lights[i]->showParamView();
		}
	}
}