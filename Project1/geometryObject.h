#pragma once
#include "baseObject.h"
#include "materialObject.h"
#include <vector>
class geometryObject : public baseObject
{
public:
	using Ptr = std::shared_ptr<geometryObject>;
	geometryObject();
	~geometryObject();
	virtual void objectShow() override;
	inline void addObject(materialObject::Ptr material) { m_materialObjects.emplace_back(material); }
private:
	std::vector<materialObject::Ptr> m_materialObjects;
};

