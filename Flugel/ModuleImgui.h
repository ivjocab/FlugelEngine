#pragma once
#ifndef __imGUI_H__

#define __imGUI_H__

#include "Module.h"
#include "SDL/include/SDL.h"
#include <stdlib.h>

class Application;

class ModuleImgui : public Module
{
public:

	ModuleImgui(Application* app, bool start_enabled = true);
	virtual ~ModuleImgui();

	bool Init();
	update_status Update(float dt);
	bool CleanUp();

public:
};

#endif // __ModuleWindow_H__