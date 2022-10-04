#include <Helpers/Globals.h>
#include <Application.h>
#include "ModuleRenderer3D.h"
#include <glew/include/GL/glew.h>
#include <SDL/include/SDL_opengl.h>
#include <GLFW/include/glfw3.h>
#include <gl/GL.h>
#include <gl/GLU.h>

#pragma comment (lib, "glew32.lib")
#pragma comment (lib, "glu32.lib")    /* link OpenGL Utility lib     */
#pragma comment (lib, "opengl32.lib") /* link Microsoft OpenGL lib   */

#include <stdint.h>
#define SET_STATE(enabled, value) if (enabled) glEnable(value); else glDisable(value);
//====================================
typedef void(*VoidFun)();
VoidFun primitive_draw_funs[] = {
	DDCube, DDCube_BadIndices, DDCube_VecIndices,
	VB_Cube, VBI_Pyramid, VBI_DiskSphere,
};

void SetOpenGLState(const OpenGLState& state) {
	SET_STATE(state.depth_test, GL_DEPTH_TEST);
	SET_STATE(state.color_material, GL_COLOR_MATERIAL);
	SET_STATE(state.cull_faces, GL_CULL_FACE);
	SET_STATE(state.lighting, GL_LIGHTING);
	SET_STATE(state.texture2D, GL_TEXTURE_2D);
	glBlendFunc(state.src_blend, state.dst_blend);
	glPolygonMode(state.poly_mode, state.poly_fill);
}

ModuleRenderer3D::ModuleRenderer3D(bool start_enabled) : Module(start_enabled)
{
	grid_state.lighting = false;
	default_state.src_blend = GL_SRC_ALPHA;
	default_state.dst_blend = GL_ONE_MINUS_SRC_ALPHA;
}

// Destructor
ModuleRenderer3D::~ModuleRenderer3D()
{}

// Called before render is available
bool ModuleRenderer3D::Init()
{
	/*LOG("Creating 3D Renderer context");*/
	bool ret = true;
	
	// Base Flags
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

	//Create context
	context = SDL_GL_CreateContext(App->window->window);

	GLenum err = glewInit();
	//LOG("Using Glew %s", glewGetString(GLEW_VERSION));

	//LOG("Vendor: %s", glGetString(GL_VENDOR));
	//LOG("Renderer: %s", glGetString(GL_RENDERER));
	//LOG("OpenGL version supported %s", glGetString(GL_VERSION));
	//LOG("GLSL: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));

	if(context == NULL)
	{
		/*LOG("OpenGL context could not be created! SDL_Error: %s\n", SDL_GetError());*/
		ret = false;
	}
	
	if(ret == true)
	{
		//Use Vsync
		if(VSYNC && SDL_GL_SetSwapInterval(1) < 0)
			//LOG("Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError());

		//Initialize Projection Matrix
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		//Check for error
		GLenum error = glGetError();
		if(error != GL_NO_ERROR)
		{
			//LOG("Error initializing OpenGL! %s\n", gluErrorString(error));
			ret = false;
		}

		//Initialize Modelview Matrix
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		//Check for error
		error = glGetError();
		if(error != GL_NO_ERROR)
		{
			//LOG("Error initializing OpenGL! %s\n", gluErrorString(error));
			ret = false;
		}
		
		glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
		glClearDepth(1.0f);
		
		//Initialize clear color
		glClearColor(0.f, 0.f, 0.f, 1.f);

		//Check for error
		error = glGetError();
		if(error != GL_NO_ERROR)
		{
			/*LOG("Error initializing OpenGL! %s\n", gluErrorString(error));*/
			ret = false;
		}
		
		GLfloat LightModelAmbient[] = {0.0f, 0.0f, 0.0f, 1.0f};
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, LightModelAmbient);
		
		GLfloat MaterialAmbient[] = {1.0f, 1.0f, 1.0f, 1.0f};
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, MaterialAmbient);

		GLfloat MaterialDiffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, MaterialDiffuse);
	}

	// Projection matrix for
	OnResize(SCREEN_WIDTH, SCREEN_HEIGHT);
	SetOpenGLState(default_state);

	InitPrimitives();

	return ret;
}

// PreUpdate: clear buffer
update_status ModuleRenderer3D::PreUpdate(float dt)
{
	SDL_GL_SwapWindow(App->window->window);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glLoadMatrixf(App->camera->GetViewMatrix());

	return UPDATE_CONTINUE;
}

// PostUpdate present buffer to screen
double cum_dt = 0;
update_status ModuleRenderer3D::PostUpdate(float dt)
{
	cum_dt += dt;
	float4 light_position = { (float)sin(cum_dt) * 5.f, 0.f, (float)cos(cum_dt) * 5.f, .5f };
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_shininess[] = { 50.0 };
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glEnable(GL_LIGHT0);

	glLightfv(GL_LIGHT0, GL_POSITION, (float*)&light_position);
	float4 neg_lp = float4(-light_position.xyz(), 1.);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, (float*)&neg_lp);

	glPointSize(10.);
	glBegin(GL_POINTS);
	glColor3f(1., 1., 1.);
	glVertex3f(light_position[0], light_position[1], light_position[2]);
	glEnd();
	RenderGrid();
	glPointSize(1.);

	if (draw_example_primitive) primitive_draw_funs[example_fun]();

	for (GPUMesh& m : meshes) {
		glEnableClientState(GL_VERTEX_ARRAY);
		glBindBuffer(GL_ARRAY_BUFFER, m.vtx_id);
		glVertexPointer(3, GL_FLOAT, 0, NULL);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m.idx_id);
		glDrawElements(GL_TRIANGLES, m.num_idx, GL_UNSIGNED_INT, NULL);
		glDisableClientState(GL_VERTEX_ARRAY);
	}

	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleRenderer3D::CleanUp()
{
	/*LOG("Destroying 3D Renderer");*/
	CleanUpPrimitives();
	SDL_GL_DeleteContext(context);

	return true;
}

#define GRID_SIZE 10

void ModuleRenderer3D::RenderGrid() const
{
	// glDisable(GL_LIGHTING);
	SetOpenGLState(grid_state);

	for (int i = 0; i < GRID_SIZE * 2 + 1; i++)
	{
		glBegin(GL_LINES);
		glColor3f(0.5f, 0.5f, 0.5f);

		//Z
		glVertex3i(GRID_SIZE - i, 0, GRID_SIZE);
		glVertex3i(GRID_SIZE - i, 0, -GRID_SIZE);

		//X
		glVertex3i(-GRID_SIZE, 0, -GRID_SIZE + i);
		glVertex3i(GRID_SIZE, 0, -GRID_SIZE + i);
		glEnd();
	}

	SetOpenGLState(default_state);
	// glEnable(GL_LIGHTING)
}

void ModuleRenderer3D::LoadMesh(const NIMesh* mesh)
{
	GPUMesh push;
	push.num_vtx = mesh->vertices.size();
	glGenBuffers(1, &push.vtx_id);
	glBindBuffer(GL_ARRAY_BUFFER, push.vtx_id);
	glBufferData(GL_ARRAY_BUFFER, push.num_vtx * sizeof(float3), mesh->vertices.data(), GL_STATIC_DRAW);

	if (mesh->normals.size() > 0) {
		glGenBuffers(1, &push.norm_id);
		glBindBuffer(GL_ARRAY_BUFFER, push.norm_id);
		glBufferData(GL_ARRAY_BUFFER, mesh->normals.size() * sizeof(float3), mesh->normals.data(), GL_STATIC_DRAW);
	}
	if (mesh->uvs.size() > 0) {
		glGenBuffers(1, &push.uvs_id);
		glBindBuffer(GL_ARRAY_BUFFER, push.uvs_id);
		glBufferData(GL_ARRAY_BUFFER, mesh->uvs.size() * sizeof(float2), mesh->uvs.data(), GL_STATIC_DRAW);
	}
	if (mesh->indices.size() > 0) {
		push.num_idx = mesh->indices.size();
		glGenBuffers(1, &push.idx_id);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, push.vtx_id);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, push.num_idx * sizeof(uint32_t), mesh->indices.data(), GL_STATIC_DRAW);

	}

	meshes.push_back(push);
}

void ModuleRenderer3D::OnResize(int width, int height)
{
	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	ProjectionMatrix = perspective(60.0f, (float)width / (float)height, 0.125f, 512.0f);
	glLoadMatrixf(&ProjectionMatrix);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
