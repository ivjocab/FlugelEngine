#pragma once

#include <Helpers/Globals.h>
#include <Helpers/Timer.h>
#include <Module.h>
#include <ModuleWindow.h>
#include <ModuleInput.h>
#include <ModuleRenderer3D.h>
#include <ModuleCamera3D.h>
#include <EngineUI/EngineUI.h>
#include <EventSystem/ModuleEventSystem.h>

#include<list>
#include<vector>

class Application
{
public:
	ModuleWindow* window;
	ModuleInput* input;
	ModuleRenderer3D* renderer3D;
	ModuleCamera3D* camera;
	EngineUI* engine_ui = &e_engine_ui;
	ModuleEventSystem* events;

private:

	Timer	ms_timer;
	float	dt;
	std::list<Module*> list_modules;

public:

	Application();
	~Application();

	bool Init();
	void SendEvents(std::vector<std::shared_ptr<Event>>& evt_vec);
	update_status Update();
	bool CleanUp();

	void Save(JSON_Object* root_node);
	void Load(JSON_Object* root_node);

private:

	void AddModule(Module* mod);
	void PrepareUpdate();
	void FinishUpdate();
};

extern Application* App;