#pragma once
#ifndef SOULFBXGEOMETRYINFO_H
#define SOULFBXGEOMETRYINFO_H

#include "glm/glm.hpp"
#include "glm/gtc/quaternion.hpp"

#include <string>
#include <vector>
namespace ztr {
	struct FbxKeyframe {
		float       time;
		glm::vec3   pos;
		glm::quat   rotation;
		glm::vec3   scale;
	};

	struct FbxBone {
		std::string                 name;
		uint8_t                     parentId;
		glm::mat4                   inverseWorldMatrix{ 1.0 };
		std::vector<FbxKeyframe>    keyframes;
	};

	struct FbxBlendshape {
		std::vector<glm::vec3>  vertices;
		std::vector<glm::vec3>  normals;
		std::vector<glm::vec3>  tangents;
	};

	struct FbxWeight {
		glm::ivec4  boneId{ 0,0,0,0 };
		glm::vec4   weight{ 0.0,0.0,0.0,0.0 };
		uint8_t     count{ 0 };
	};

	struct FbxMesh
	{
		using FbxWeights = std::vector<FbxWeight>;
		using FbxBlendshapes = std::vector<FbxBlendshape>;

		std::string             name;
		std::vector<glm::vec3>  vertices;
		std::vector<glm::vec3>  normals;
		std::vector<glm::vec3>  tangents;
		std::vector<glm::vec2>  uvs;
		FbxWeights              weights;

		std::vector<uint32_t>   indices;
		std::vector<FbxBone>    bones;
		FbxBlendshapes          blendshapes;
	};
}
#endif // SOULFBXGEOMETRYINFO_H