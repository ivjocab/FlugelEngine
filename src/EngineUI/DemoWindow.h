#pragma once

#include "EngineUI/ui_item.h"
#include "EngineUI/MenuBar.h"

class DemoWindow : UI_Item {
public:
	DemoWindow() : UI_Item("DemoWindow") {}

	void Update() {
		ImGui::ShowDemoWindow(&active);
	}
};

DemoWindow demowindow;
