#pragma once
#include "Module.h"
#include "Globals.h"

class Motor : public Module
{
public:
	Motor(Application* app, bool start_enabled = true);
	~Motor();

	bool Start();
	update_status PreUpdate();
	update_status PostUpdate();
	bool CleanUp();

private:

	bool debug;
};