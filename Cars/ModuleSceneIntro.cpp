#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
#include "PhysBody3D.h"
#include "ModulePlayer.h"
#include "ModulePhysics3D.h"
#include "Color.h"
#include "glut/glut.h"
#include "ModuleAudio.h"

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	return ret;
}

void angleAndAxisFromEuler(float psi, float theta, float phi, float& angle, vec3& axis)
{
	float m[3][3];

	m[0][0] = cos(theta) * cos(psi);
	m[0][1] = cos(psi) * sin(theta) * sin(phi) - cos(phi) * sin(psi);
	m[0][2] = cos(psi) * cos(psi) * sin(theta) + sin(psi) * sin(phi);
	m[1][0] = cos(theta) * sin(psi);
	m[1][1] = sin(psi) * sin(theta) * sin(phi) + cos(phi) * cos(psi);
	m[1][2] = cos(phi) * sin(psi) * sin(theta) - cos(psi) * sin(phi);
	m[2][0] = -sin(theta);
	m[2][1] = cos(theta) * sin(phi);
	m[2][2] = cos(theta) * cos(phi);

	angle = acos((m[0][0] + m[1][1] + m[2][2] - 1) / 2.0f);

	axis.x = (m[2][1] - m[1][2]) / (2 * sin(angle));
	axis.y = (m[0][2] - m[2][0]) / (2 * sin(angle));
	axis.z = (m[1][0] - m[0][1]) / (2 * sin(angle));

	axis = normalize(axis);
}

void angleAndAxisFromRotMat(mat4x4 m, float& angle, vec3& axis)
{
	angle = acos((m[0] + m[5] + m[10] - 1) / 2.0f);

	axis.x = (m[9] - m[6]) / (2 * sin(angle));
	axis.y = (m[2] - m[8]) / (2 * sin(angle));
	axis.z = (m[4] - m[1]) / (2 * sin(angle));

	axis = normalize(axis);
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	return true;
}

// Update
update_status ModuleSceneIntro::Update(float dt)
{

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{

}

void ModuleSceneIntro::outputText(int x, int y, float r, float g, float b, char* string)
{
	glColor3f(r, g, b);
	glRasterPos2f(x, y);
	int len, i;
	len = (int)strlen(string);
	for (i = 0; i < len; i++) 
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);
	}
}


