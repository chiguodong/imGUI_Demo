#pragma once
#include "shaderJointer.h"
#include "materialParamUnion.h"
#include "glm/glm.hpp"

class materialParamEditor
{
public:
	using Ptr = std::shared_ptr<materialParamEditor>;
	materialParamEditor();
	~materialParamEditor();
	inline void setName(std::string name) { m_name = name; }
	void showParamView();
	materialParamUnion p;

	bool showParamViewFlag{ false };
	void updateUniform(std::string uniformName, float value);
	void updateUniform(std::string uniformName, glm::vec3 value);
	void updateUniform(std::string uniformName, std::string value);

private:
	std::string m_name{""};
//private:
};

