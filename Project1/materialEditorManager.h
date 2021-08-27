#pragma once
#include "materialParamEditor.h"
#include <vector>
class materialEditorManager
{
protected:
	materialEditorManager();
	~materialEditorManager();
public:
	static materialEditorManager* getManager();
	void addParamEditor(materialParamEditor::Ptr editor) { m_editors.emplace_back(editor); }
	void show();
	void deleteParamEditor(materialParamEditor::Ptr editor);//TODO: 
protected:
	std::vector<materialParamEditor::Ptr> m_editors;
};

