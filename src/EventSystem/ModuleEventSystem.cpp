#include "ModuleEventSystem.h"
#include <Application.h>


void ModuleEventSystem::SendEvents() {
	while (buffer_vec.size() > 0) {}
	buffer_vec.swap(event_vec);
	App->SendEvents(buffer_vec);
}