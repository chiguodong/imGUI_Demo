#pragma once

#ifndef NODESTREEVIEWS_H
#define NODESTREEVIEWS_H

#include "imgui/imgui.h"
#include "baseObject.h"
#include "fbxReader.h"
#include "geometryObject.h"
#include "IBLObject.h"
#include "lightObject.h"
#include <vector>

using namespace ztr;
class nodesTreeViews {
public:
	nodesTreeViews();
	~nodesTreeViews();

	void showTreeNodes();
	void showMenu();
	void showFilter();
	void refreshNodes(std::shared_ptr<fbxReader> reader);
	//inline void addObject(baseObject::Ptr object) { m_objects.emplace_back(object); }
	void deleteObject();
private:
	//std::vector<baseObject::Ptr> m_objects;
	std::shared_ptr<geometryObject> m_geometry;
	std::shared_ptr<lightObject> m_light0;
	std::shared_ptr<lightObject> m_light1;
	std::shared_ptr<IBLObject> m_IBL;
	bool showFbxFilter{false};
	std::shared_ptr<fbxReader> reader{nullptr};
	bool hasGeometry{false};
	std::string m_resoucePath{ "" };
};

#endif // NODESTREEVIEWS_H