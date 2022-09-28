#pragma once

#include <Helpers/Globals.h>
#include <Helpers/Timer.h>
#include <Module.h>
#include <ModuleWindow.h>
#include <ModuleInput.h>
#include <ModuleRenderer3D.h>
#include <ModuleCamera3D.h>
//#include <ModuleEngineUI.h>
//#include <ModuleEventSystem.h>

#include<list>
#include<vector>

class Application
{
public:
	ModuleWindow* window;
	ModuleInput* input;
	ModuleRenderer3D* renderer3D;
	ModuleCamera3D* camera;
	//ModuleEngineUI* engine_ui = &e_engine_ui;
	//ModuleEventSystem* events;

private:

	Timer	ms_timer;
	float	dt;
	std::list<Module*> list_modules;

public:

	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();

private:

	void AddModule(Module* mod);
	void PrepareUpdate();
	void FinishUpdate();
};

extern Application* App;