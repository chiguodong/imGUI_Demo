#include "fbxReader.h"
#include <iostream>

using namespace Assimp;

static aiScene*                     s_scene{ nullptr };
static std::vector<aiNode*>         s_allNodes;
static std::vector<std::string>     s_names;

static void traversalAllNodes(aiNode* node) {
	if (node) {
		s_allNodes.emplace_back(node);
		s_names.emplace_back(node->mName.data);
	}

	for (int i = 0; i < node->mNumChildren; ++i) {
		traversalAllNodes(node->mChildren[i]);
	}
}

void fbxReader::read() {
	Importer import;
	const aiScene* scene = import.ReadFile(m_path, aiProcess_Triangulate | aiProcess_GenSmoothNormals |
		aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
		std::cout << "ERROR::ASSIMP::" << import.GetErrorString() << std::endl;
		return;
	}
	else {
		m_isRead = true;
	}

	//todo: 有更好的办法？
	s_scene = const_cast<aiScene*>(scene);

	//read
	processNode(scene->mRootNode, scene);
}

void fbxReader::processNode(aiNode *node, const aiScene *scene) {
	// 处理节点所有的网格（如果有的话）
	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
		m_meshes.emplace_back(processMesh(mesh, scene));
	}
	// 接下来对它的子节点重复这一过程
	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		processNode(node->mChildren[i], scene);
	}
}


FbxMesh fbxReader::processMesh(aiMesh* mesh, const aiScene* scene) {
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec3> tangents;
	std::vector<glm::vec2> uvs;

	std::vector<uint32_t> indices;
	//vector<Texture> textures;

	//vertex info
	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		glm::vec3 vertex;
		glm::vec3 normal;
		glm::vec3 tangent;
		glm::vec2 uv{ 0.0f,0.0f };
		// 处理顶点位置、法线和纹理坐标
		vertex.x = mesh->mVertices[i].x; vertex.y = mesh->mVertices[i].y; vertex.z = mesh->mVertices[i].z;
		if (mesh->HasNormals()) {
			normal.x = mesh->mNormals[i].x; normal.y = mesh->mNormals[i].y; normal.z = mesh->mNormals[i].z;
		}

		if (mesh->HasTangentsAndBitangents()) {
			tangent.x = mesh->mTangents[i].x;
			tangent.y = mesh->mTangents[i].y;
			tangent.z = mesh->mTangents[i].z;
		}

		if (mesh->mTextureCoords[0]) // 网格是否有纹理坐标？
		{
			uv.x = mesh->mTextureCoords[0][i].x; uv.y = mesh->mTextureCoords[0][i].y;
		}

		vertices.emplace_back(std::move(vertex));
		normals.emplace_back(std::move(normal));
		tangents.emplace_back(std::move(tangent));
		uvs.emplace_back(std::move(uv));
	}
	// index info
	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; j++)
			indices.emplace_back(face.mIndices[j]);
	}
	FbxMesh fbxMesh;
	fbxMesh.name = std::string(mesh->mName.data);
	fbxMesh.vertices = std::move(vertices);
	fbxMesh.normals = std::move(normals);
	fbxMesh.tangents = std::move(tangents);
	fbxMesh.uvs = std::move(uvs);
	fbxMesh.indices = std::move(indices);

	// material
	/*if(mesh->mMaterialIndex >= 0)
	{
		aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
		vector<Texture> diffuseMaps = loadMaterialTextures(material,
											aiTextureType_DIFFUSE, "texture_diffuse");
		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
		vector<Texture> specularMaps = loadMaterialTextures(material,
											aiTextureType_SPECULAR, "texture_specular");
		textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
	}*/
	//auto ans = Mesh(vertices, indices, textures);
	//

	return fbxMesh;
}
