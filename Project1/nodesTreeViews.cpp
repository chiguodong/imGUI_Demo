#include "nodesTreeViews.h"

nodesTreeViews::nodesTreeViews() {

}

nodesTreeViews::~nodesTreeViews() {

}


void nodesTreeViews::showTreeNodes() {
	bool p_open = true;

	const ImGuiViewport* main_viewport = ImGui::GetMainViewport();
	ImGui::SetNextWindowPos(ImVec2(main_viewport->WorkPos.x + 650, main_viewport->WorkPos.y + 20), ImGuiCond_FirstUseEver);
	ImGui::SetNextWindowSize(ImVec2(550, 680), ImGuiCond_FirstUseEver);

	if (!ImGui::Begin("nodes list"))//could set window flags in second param
	{
		// Early out if the window is collapsed, as an optimization.
		ImGui::End();
		return;
	}
	for (auto e : m_objects) {
		e->objectShow();
	}
	ImGui::End();
}

