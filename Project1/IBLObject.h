#pragma once

#include "baseObject.h"
#include <string>

class IBLObject : public baseObject
{
public:
	IBLObject();
	~IBLObject();
	virtual void objectShow() override;
private:
	char IBLFolder[64]{ "" };
	std::string m_resoucePath{ "" };
};

