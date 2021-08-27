#pragma once
#ifndef SOULGEOMETRYOBJECT_H
#define SOULGEOMETRYOBJECT_H

#include "baseObject.h"
#include <vector>
class geometryObject : public baseObject
{
public:
	using Ptr = std::shared_ptr<geometryObject>;
	geometryObject();
	~geometryObject();
	virtual void objectShow() override;
	inline void addObject(baseObject::Ptr material) { m_materialObjects.emplace_back(material); }
	inline void clearObject();
	void clearMaterialShowFlag();
private:
	std::vector<baseObject::Ptr> m_materialObjects;
};

#endif SOULGEOMETRYOBJECT_H