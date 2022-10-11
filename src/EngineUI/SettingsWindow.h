#pragma once

#include "EngineUI/ui_item.h"
#include "EngineUI.h"

class SettingsWindow : UI_Item {
public:
	SettingsWindow() : UI_Item("Configuration") {};
	void Start();

	void PerformanceGraphs();
	void WindowOptions();
	void HardwareInfo();
	void RenderOptions();

	void Update() {
		ImGui::Begin(name.c_str(), &active);

		if (ImGui::CollapsingHeader("Performance")) PerformanceGraphs();
		if (ImGui::CollapsingHeader("Windowing")) WindowOptions();
		if (ImGui::CollapsingHeader("Hardware")) HardwareInfo();

		if (ImGui::CollapsingHeader("Renderer")) RenderOptions();

		ImGui::End();
	}

	void ReceiveEvents(std::vector<std::shared_ptr<Event>>& evt_vec);
};
