#pragma once
#include "baseObject.h"
#include "fbxGeometryInfo.h"
#include <vector>
class materialObject :	public baseObject
{
public:
	using Ptr = std::shared_ptr<materialObject>;
	materialObject();
	~materialObject();
	virtual void objectShow();

	void setMesh(std::shared_ptr<FbxMesh> mesh);

private:
	std::shared_ptr<FbxMesh> m_mesh;
};
