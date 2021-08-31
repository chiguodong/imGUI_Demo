#pragma once
#include "lightParamUnion.h"
#include "SoulEditorRender.hpp"
using namespace Soul;
class lightParamEditor
{
public:
	using Ptr = std::shared_ptr<lightParamEditor>;
	lightParamEditor();
	~lightParamEditor();
	void showParamView();
	void showDirLightView();
	void showSpotLightView();
	void showPointLightView();
	void showLightView();
	void setDefaultParam();
	const char* LIHGT_TYPE[3] = { "directionLight", "spotLight", "pointLight" };
	int lightTypeIndex{ 0 };
	void setLightNum(int input) { lightNum = input; }

	bool showParamViewFlag{false};

protected:
	lightParamUnion p;
	editorRender* m_render;
	int lightNum{ 0 };//TODO: manage it into manager
};