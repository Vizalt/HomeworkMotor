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
	
	// Set physics properties of the ball
	ball.mass = 10; // kg
	ball.surface = 2; // m^2
	ball.cd = 0.4;
	ball.cl = 1.2;

	// Set initial position and velocity of the ball
	ball.x = ball.y = 0.0;
	ball.vx = 10.0;
	ball.vy = 5.0;

	return true;
}

// 
update_status Motor::PreUpdate()
{
	
	return UPDATE_CONTINUE;
}

update_status Motor::Update()
{
	// Step #0: Reset total acceleration and total accumulated force of the ball (clear old values)
	ball.fx = ball.fy = 0.0;
	ball.ax = ball.ay = 0.0;
	// Step #1: Compute forces

		// Compute Gravity force
	double fgx = ball.mass * 0.0;
	double fgy = ball.mass * -10.0; // Let's assume gravity is constant and downwards

	// Add gravity force to the total accumulated force of the ball
	ball.fx += fgx;
	ball.fy += fgy;

	// Step #2: 2nd Newton's Law: SUM_Forces = mass * accel --> accel = SUM_Forces / mass
	ball.ax = ball.fx / ball.mass;
	ball.ay = ball.fy / ball.mass;

	// Step #3: Integrate --> from accel to new velocity & new position. 
	integrator_velocity_verlet(ball, dt);

	// Step #4: solve collisions
	if (ball.y < ground.y)
	{
		// For now, just stop the ball when it reaches the ground.
		ball.vx = ball.vy = 0.0;
		ball.ax = ball.ay = 0.0;
		ball.fx = ball.fy = 0.0;
		ball.physics_enabled = false;
	}

	return UPDATE_CONTINUE;
}


// Integration scheme: Velocity Verlet
// You should modularise all your algorithms into subroutines. Including the ones to compute forces.
void Motor::integrator_velocity_verlet(Ball& ball, double dt)
{
	ball.x += ball.vx * dt + 0.5 * ball.ax * dt * dt;
	ball.y += ball.vy * dt + 0.5 * ball.ay * dt * dt;
	ball.vx += ball.ax * dt;
	ball.vy += ball.ay * dt;
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
