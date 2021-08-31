#pragma once
#include "baseObject.h"
#include "lightParamUnion.h"
#include "lightParamEditor.h"
#include "lightEditorManager.h"

class lightObject : public baseObject
{
public:
	lightObject();
	~lightObject();
	virtual void objectShow();
	void setLightNum(int lightNum) { m_editorView->setLightNum(lightNum); }

private:
	lightEditorManager* lightManager;
	lightParamEditor::Ptr m_editorView;
};

