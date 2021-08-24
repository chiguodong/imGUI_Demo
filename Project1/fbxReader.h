#pragma once
#ifndef SOULFBXREADER_H
#define SOULFBXREADER_H

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

#include "glm/glm.hpp"
#include "glm/gtc/quaternion.hpp"

#include "fbxGeometryInfo.h"
#include <string>
#include <vector>

class fbxReader
{
public:
	explicit fbxReader(const std::string& path) :m_path{ path } {}

public:
	inline void setPath(const std::string& path) { m_path = path; }
	inline bool isRead() { return m_isRead; }
	void        read();
	inline void setFileName(const std::string& name) { m_fileName = name; }

	std::vector<FbxMesh>&       getMeshes() { return m_meshes; }

protected:
	void            processNode(aiNode* node, const aiScene* scene);
	FbxMesh			processMesh(aiMesh* mesh, const aiScene* scene);

protected:
	bool                        m_isRead{ false };
	std::string                 m_path;
	std::string                 m_fileName{""};
	std::vector<FbxMesh>		m_meshes;

};

#endif // SOULFBXREADER_H

