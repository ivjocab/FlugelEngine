#pragma once
using namespace std;

#include "Globals.h"
#include "Timer.h"
#include "Module.h"
#include "ModuleWindow.h"
#include "ModuleImgui.h"
#include "ModuleInput.h"
#include "ModuleCamera3D.h"
#include <list>
#include <vector>

class Application
{
public:
	ModuleWindow* window;
	ModuleInput* input;
	ModuleCamera3D* camera;
	ModuleImgui* imgui;

private:

	Timer	ms_timer;
	float	dt;
	std::vector<Module*> list_modules;
	
	

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