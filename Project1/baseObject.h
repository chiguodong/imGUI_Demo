#pragma once

#include <string>
class baseObject
{
public:
	using Ptr = std::shared_ptr<baseObject>;
	baseObject();
	~baseObject();
	virtual void objectShow();
	inline void setName(const std::string name) { m_name = name; }
protected:
	std::string m_name{""};
};

