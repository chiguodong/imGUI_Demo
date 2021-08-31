#pragma once
#include "glm/glm.hpp"
#include "imgui/imgui.h"
#include <string>

class materialParamUnion {
public:
	struct BRDFParam {
		float matallic{0.0};
		float roughness{ 0.0 };
		float fresnelF0{ 0.04 };
		char mraMap[64]{"default/white.png"};
		char diffuseMap[64]{"default/white.png"};
		char normalMap[64]{"default/black.png"};
	} BRDF;
	struct commonParam {
		float wrap{ 0.0 };
		float specularIntensity{ 1.0 };
		float diffuseIntensity{ 1.0 };
	} common;
	struct anisotropicParam {
		float anisotropic{ 0.0 };//(-1.0 , 1.0)
		char directionMap[64]{"default/black.png"};
	}anisotropic;
	struct clearCoatParam {
		float clearCoat{ 0.0 };
		float clearCoatRoughness{ 0.0 };
		ImVec4 clearCoatColor = ImVec4(114.0f / 255.0f, 144.0f / 255.0f, 154.0f / 255.0f, 200.0f / 255.0f);
	}clearCoat;
	struct subsurfaceParam {
		float subsurfacePower{ 1.0 };
		glm::vec3 subsurfaceColor{ glm::vec3(1.0, 1.0, 1.0) };
		char depthMap[64]{"default/black.png"};
	}subsurface;
}; 
