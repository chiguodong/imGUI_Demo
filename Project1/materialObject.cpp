
#include <imgui/imgui.h>
#include "materialObject.h"

materialObject::materialObject() {

}

materialObject::~materialObject() {

}

void materialObject::objectShow() {
	if (ImGui::TreeNode(m_name.c_str())) {
		if (ImGui::IsItemClicked()) {
			ImGui::Text("lalala lalala");
		}
		ImGui::TreePop();
	}
}