#pragma once
#include "shaderJointer.h"
#include "materialParamUnion.h"
#include "shaderJointer.h"
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
	void init() { findDefaultMap();  setDefaultParam();}
	void findDefaultMap();
	void setDefaultParam();

	bool showParamViewFlag{ false };
	void showSpecular(int specularIndex);
	void showClearCoat(int clearCoatIndex);
	void showSubsurface(int SubsurfaceIndex);

	void addClearCoatShader();
	void addSpecularShader();
	void addSubsurfaceShader();


	void updateUniform(std::string uniformName, float value);
	void updateUniform(std::string uniformName, glm::vec3 value);
	void updateUniform(std::string uniformName, std::string value);

private:
	std::string m_name{""};
	std::string m_resoucePath{""};

	std::shared_ptr<shaderJointer> jointer;

	int specularTypeIndex = 0;
	int clearCoatTypeIndex = 0;
	int subsurfaceTypeIndex = 0;

};