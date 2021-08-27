#pragma once
#ifndef SOULMATERIALOBJECT_H
#define SOULMATERIALOBJECT_H

#include "baseObject.h"
#include "fbxGeometryInfo.h"
#include "materialParamEditor.h"
#include <vector>

using namespace ztr;
class materialObject :	public baseObject
{
public:
	using Ptr = std::shared_ptr<materialObject>;
	materialObject();
	~materialObject();
	virtual void objectShow();

	void setMesh(std::shared_ptr<FbxMesh> mesh);
	inline void setFatherGeometry(baseObject::Ptr geo) { m_geometry = geo; }
	inline void clearShow() { m_editorView->showParamViewFlag = false; }

private:
	std::shared_ptr<FbxMesh> m_mesh;
	materialParamEditor::Ptr m_editorView;
	baseObject::Ptr m_geometry;
};

#endif SOULMATERIALOBJECT_H