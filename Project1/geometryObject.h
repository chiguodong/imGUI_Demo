#pragma once
#include "baseObject.h"
#include <vector>
class geometryObject : public baseObject
{
public:
	geometryObject();
	~geometryObject();
	virtual void objectShow();
private:
	std::vector<std::string> m_materialObject;
};

