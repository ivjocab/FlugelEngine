#ifndef __ModuleWindow_H__
#define __ModuleWindow_H__

#include "Module.h"

class Application;

class GLFWwindow;

class ModuleWindow : public Module
{
public:

	ModuleWindow(Application* app, bool start_enabled = true);

	// Destructor
	virtual ~ModuleWindow();

	bool Init();
	update_status Update(float dt);
	bool CleanUp();

	void SetTitle(const char* title);

	bool WindowQuit();

public:
	//The window we'll be rendering to
	GLFWwindow* window;
};

#endif // __ModuleWindow_H__