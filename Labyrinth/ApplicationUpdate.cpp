#include "Application.h"

#include "config.h"
 
void Application::onUpdate()
{
	if (config::IS_DEBUG) 
	{
		static Uint32 last_time = SDL_GetTicks();
		const float delta_time = (SDL_GetTicks() - last_time) / 1000.0f;
		cameraManager.Update(delta_time);
		last_time = SDL_GetTicks();
	}
}