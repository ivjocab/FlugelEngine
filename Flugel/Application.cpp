#include "Application.h"

Application::Application()
{
	window = new ModuleWindow(this);
	imgui = new ModuleImgui(this);
	input = new ModuleInput(this);
	camera = new ModuleCamera3D(this);

	// The order of calls is very important!
	// Modules will Init() Start() and Update in this order
	// They will CleanUp() in reverse order

	// Main Modules
	AddModule(window);
	AddModule(imgui);
	AddModule(input);
	AddModule(camera);
}

Application::~Application()
{
	for (size_t i = 0; i < list_modules.size(); i++)
	{
		delete list_modules[i];
	}
}

bool Application::Init()
{
	bool ret = true;

	// Call Init() in all modules
	for (size_t i = 0; i < list_modules.size(); i++)
	{
		list_modules[i]->Init();
	}

	for (size_t i = 0; i < list_modules.size(); i++)
	{
		list_modules[i]->Start();
	}

	// After all Init calls we call Start() in all modules
	LOG("Application Start --------------");
	
	ms_timer.Start();
	return ret;
}

// ---------------------------------------------
void Application::PrepareUpdate()
{
	dt = (float)ms_timer.Read() / 1000.0f;
	ms_timer.Start();
}

// ---------------------------------------------
void Application::FinishUpdate()
{
}

// Call PreUpdate, Update and PostUpdate on all modules
update_status Application::Update()
{
	update_status ret = UPDATE_CONTINUE;
	PrepareUpdate();
	
	for (size_t i = 0; i < list_modules.size(); i++)
	{
		list_modules[i]->PreUpdate(dt);
	}

	for (size_t i = 0; i < list_modules.size(); i++)
	{
		list_modules[i]->Update(dt);
	}

	for (size_t i = 0; i < list_modules.size(); i++)
	{
		list_modules[i]->PostUpdate(dt);
	}

	FinishUpdate();
	return ret;
}

bool Application::CleanUp()
{
	bool ret = true;

	for (size_t i = 0; i < list_modules.size(); i++)
	{
		list_modules[i]->CleanUp();
	}

	return ret;
}

void Application::AddModule(Module* mod)
{
	list_modules.push_back(mod);
}