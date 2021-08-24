#pragma once
#include "imgui/imgui.h"
#include "baseObject.h"
#include "fbxReader.h"
#include <vector>

class nodesTreeViews {
public:
	nodesTreeViews();
	~nodesTreeViews();

	void showTreeNodes();
	void showMenu();
	void showFilter();
	void refreshNodes();
	inline void addObject(baseObject::Ptr object) { m_objects.emplace_back(object); }
	void deleteObject();
private:
	std::vector<baseObject::Ptr> m_objects;
	bool showFbxFilter{false};
	std::shared_ptr<fbxReader> reader{nullptr};
};