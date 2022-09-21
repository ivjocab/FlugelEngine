#include "Globals.h"
#include "Application.h"
#include "ModuleWindow.h"

#include "glfw/include/GLFW/glfw3.h"
#include "glew/include/GL/glew.h"

ModuleWindow::ModuleWindow(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	window = NULL;
}

// Destructor
ModuleWindow::~ModuleWindow()
{
}

// Called before render is available
bool ModuleWindow::Init()
{
    bool ret = false;
	LOG("Init SDL window & surface");


    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /* Loop until the user closes the window */

	return ret;
}

update_status ModuleWindow::Update(float dt)
{
    /* Render here */
    glClear(GL_COLOR_BUFFER_BIT);

    /* Swap front and back buffers */
    glfwSwapBuffers(window);

    /* Poll for and process events */
    glfwPollEvents();
}

// Called before quitting
bool ModuleWindow::CleanUp()
{
	LOG("Destroying SDL window and quitting all SDL systems");

	//Quit SDL subsystems
    glfwTerminate();
	return true;
}

void ModuleWindow::SetTitle(const char* title)
{
    glfwSetWindowTitle(window, title);
}

bool ModuleWindow::WindowQuit()
{
    return glfwWindowShouldClose(window);
}
