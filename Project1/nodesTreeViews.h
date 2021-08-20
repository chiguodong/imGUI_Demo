#pragma once
#include "imgui/imgui.h"
#include "baseObject.h"
#include <vector>

class nodesTreeViews {
public:
	nodesTreeViews();
	~nodesTreeViews();

	void showTreeNodes();
	inline void addObject(baseObject::Ptr object) { m_objects.emplace_back(object); }
	void deleteObject();
private:
	std::vector<baseObject::Ptr> m_objects;
};