#pragma once

#pragma once
#include <Module.h>
#include <helpers/Globals.h>
#include "ImGui/imgui.h"
#include <SDL/include/SDL.h>
#include <vector>
#include <memory>

class UI_Item;

class EngineUI : public Module
{
public:
	EngineUI(bool start_updated);
	~EngineUI();

	bool IsStaticModule() { return true; }

	bool Start();
	update_status Update(float dt);
	update_status PostUpdate(float dt);
	bool CleanUp();

	void ReceiveEvents(std::vector<std::shared_ptr<Event>>& evt_vec);

	bool GetEvent(SDL_Event* e);

	void EngineUI_RegisterItem(UI_Item* item);
	void EngineUI_RequireUpdate(bool window_state)
	{
		require_update = require_update || !window_state;
	}

private:
	std::vector<UI_Item*> items;
	std::vector<uint32_t> active_items;
	bool require_update = false;

private:



	void EngineUI_UpdateActives();
};

extern EngineUI e_engine_ui;