#pragma once
#include "glm/glm.hpp"
#include <string>

class materialParamUnion {
public:
	struct BRDFParam {
		float matallic{0.0};
		float roughness{ 0.0 };
		float fresnelF0{ 0.0 };
		std::string mraMap{""};
		std::string diffuse{""};
		std::string normalMap{""};
	} BRDF;
	struct commonParam {
		float wrap{ 0.0 };
		float specularIntensity{ 1.0 };
		float diffuseIntensity{ 1.0 };
	} common;
	struct anitropicParam {
		float anitropic{ 0.0 };//(-1.0 , 1.0)
		std::string directionMap;
	};
	struct clearCoatParam {
		float clearCoat{ 0.0 };
		float clearCoatRoughness{ 0.0 };
		glm::vec3 clearCoarColor{ glm::vec3(1.0, 1.0, 1.0) };
	};
	struct subsurfaceParam {
		float subsurfacePower{ 1.0 };
		glm::vec3 subsurfaceColor{ glm::vec3(1.0, 1.0, 1.0) };
		std::string depthMap;
	};
};
