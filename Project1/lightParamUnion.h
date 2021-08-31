#pragma once
#include "glm/glm.hpp"
#include "imgui/imgui.h"
#include <string>

class lightParamUnion {
public:
	float lightType{0};//0:directionLight 1: spotLight 2:pointLight
	glm::vec3 intensity{ glm::vec3(10000.0, 10000.0, 10000.0) };
	glm::vec3 position{ glm::vec3(0.0, 0.0, -400.0) };

	struct DirLight {
		float position[3]{ 0.0, 0.0, -400.0 };
		float direction[3]{ 0.0, 0.0, -1.0 };
		float intensity[3]{ 10000.0, 10000.0, 10000.0 };
	}dirLight;

	struct PointLight {
		float position[3]{ 0.0, 0.0, -400.0 };
		float intensity[3]{ 10000.0, 10000.0, 10000.0 };
	}pointLight;

	struct SpotLight {
		float position[3]{ 0.0, 0.0, -400.0 };
		float direction[3]{ 0.0, 0.0, -1.0 };
		float intensity[3]{ 10000.0, 10000.0, 10000.0 };
		float cutOff;
		float outerCutOff;
	}spotLight;
};
