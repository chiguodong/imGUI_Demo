#pragma once

#include <string>
class baseObject:public std::enable_shared_from_this<baseObject>
{
public:
	using Ptr = std::shared_ptr<baseObject>;
	baseObject();
	~baseObject();
	virtual void objectShow();
	inline void setName(const std::string name) { m_name = name; }
protected:
	std::string m_name{""};
public:
	template<class T>
	std::shared_ptr<T>  asTObject() { return std::dynamic_pointer_cast<T>(shared_from_this()); }
};

