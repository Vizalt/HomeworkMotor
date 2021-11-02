#include "Globals.h"
#include "Application.h"
#include "Motor.h"
#include "math.h"

// TODO 1: Include Box 2 header and library

Motor::Motor(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	debug = true;
}

// Destructor
Motor::~Motor()
{
}

bool Motor::Start()
{
	LOG("Creating Physics 2D environment");

	
	return true;
}

// 
update_status Motor::PreUpdate()
{
	
	return UPDATE_CONTINUE;
}

// 
update_status Motor::PostUpdate()
{
	
	if(App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
		debug = !debug;

	if(!debug)
		return UPDATE_CONTINUE;




	return UPDATE_CONTINUE;
}


// Called before quitting
bool Motor::CleanUp()
{
	LOG("Destroying physics world");

	// Delete the whole physics world!

	return true;
}
