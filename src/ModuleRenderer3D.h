#pragma once
#include <Module.h>
#include <Helpers/Globals.h>
#include <GLM.hpp>
#include <Helpers/glmath.h>
#include <vector>
#include <EventSystem/Event.h>
#include "RendererTypes.h"
#include "Primitives/Primitives.h"
#define MAX_LIGHTS 8

void SetOpenGLState(const OpenGLState& state);

class ModuleRenderer3D : public Module
{
public:
	ModuleRenderer3D(bool start_enabled = true);
	~ModuleRenderer3D();

	bool Init();
	update_status PreUpdate(float dt);
	update_status PostUpdate(float dt);
	bool CleanUp();

	void ReceiveEvents(std::vector<std::shared_ptr<Event>>& evt_vec);

	void OnResize(int width, int height);

	void RenderGrid() const;

	void LoadMesh(const NIMesh* mesh);

public:

	SDL_GLContext context;
	mat3x3 NormalMatrix;
	mat4x4 ModelMatrix, ViewMatrix, ProjectionMatrix;

	const char* glsl_version = "#version 330";

	// State
	OpenGLState default_state;
	OpenGLState grid_state;
	std::vector<OpenGLState> state_stack;
	std::vector<OpenGLState> states;
	uint32_t example_fun = 0;
	bool draw_example_primitive = false;

	std::vector<GPUMesh> meshes;
};