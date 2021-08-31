#pragma once
#include "lightParamEditor.h"

class lightEditorManager
{
public:
	lightEditorManager();
	~lightEditorManager();
	void showObject();
	static lightEditorManager* getManager();
	void addLight(lightParamEditor::Ptr input) { m_lights.emplace_back(input); }

private:
	struct light {
		lightParamEditor::Ptr lightEditor;
		int lightType;
		int lightNum;
	};

	std::vector<lightParamEditor::Ptr> m_lights;
};

