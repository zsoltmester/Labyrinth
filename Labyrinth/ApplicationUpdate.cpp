#include "Application.h"

void Application::onUpdate()
{
	static Uint32 last_time = SDL_GetTicks();
	float delta_time = (SDL_GetTicks() - last_time) / 1000.0f;
	cameraManager.Update(delta_time);
	last_time = SDL_GetTicks();
}