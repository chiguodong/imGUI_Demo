#include "materialEditorManager.h"

materialEditorManager::materialEditorManager() {

}

materialEditorManager::~materialEditorManager() {

}

materialEditorManager* materialEditorManager::getManager() {
	static materialEditorManager materialManager;
	return &materialManager;
}

void materialEditorManager::show() {
	for (int i = 0; i < m_editors.size(); i++) {
		if (m_editors[i]->showParamViewFlag) m_editors[i]->showParamView();
	}
}