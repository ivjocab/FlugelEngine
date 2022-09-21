#pragma once
#ifndef __imGUI_H__

#define __imGUI_H__

#include "Module.h"
#include "SDL/include/SDL.h"

class Application;

class imGUI : public Module
{
public:

	imGUI(Application* app, bool start_enabled = true);

	// Destructor
	virtual ~imGUI();

	bool Init();
	bool Update();
	bool CleanUp();

public:
};

#endif // __ModuleWindow_H__