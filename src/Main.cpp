#include <stdlib.h>
#include <Application.h>
#include <helpers/Globals.h>
#include <SDL/include/SDL.h>
#pragma comment( lib, "SDL2.lib" )
#pragma comment( lib, "SDL2main.lib" )

enum main_states
{
	MAIN_CREATION,
	MAIN_START,
	MAIN_UPDATE,
	MAIN_FINISH,
	MAIN_EXIT
};

#include <iostream>


Application* App = NULL;
int main(int argc, char** argv)
{
	//PLOG("Starting game '%s'...", TITLE);

	int main_return = EXIT_FAILURE;
	main_states state = MAIN_CREATION;

	while (state != MAIN_EXIT)
	{
		switch (state)
		{
		case MAIN_CREATION:

		/*	PLOG("-------------- Application Creation --------------");*/
			App = new Application();
			state = MAIN_START;
			break;

		case MAIN_START:

			/*PLOG("-------------- Application Init --------------");*/
			if (App->Init() == false)
			{
				/*PLOG("Application Init exits with ERROR");*/
				state = MAIN_EXIT;
			}
			else
			{
				state = MAIN_UPDATE;
				/*PLOG("-------------- Application Update --------------");*/
			}

			break;

		case MAIN_UPDATE:
		{
			int update_return = App->Update();

			if (update_return == UPDATE_ERROR)
			{
				/*PLOG("Application Update exits with ERROR");*/
				state = MAIN_EXIT;
			}

			if (update_return == UPDATE_STOP)
				state = MAIN_FINISH;
		}
		break;

		case MAIN_FINISH:

			/*PLOG("-------------- Application CleanUp --------------");*/
			if (App->CleanUp() == false)
			{
				/*PLOG("Application CleanUp exits with ERROR");*/
			}
			else
				main_return = EXIT_SUCCESS;

			state = MAIN_EXIT;

			break;

		}
	}

	delete App;
	/*PLOG("Exiting game '%s'...\n", TITLE);*/
	return main_return;
}