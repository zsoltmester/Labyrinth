#include "Application.h"

#include "config.h"

void Application::onKeyboardDown(SDL_KeyboardEvent& key)
{
	if (config::isDebug) {
		cameraManager.KeyboardDown(key);
	}
}

void Application::onKeyboardUp(SDL_KeyboardEvent& key)
{
	if (config::isDebug) {
		cameraManager.KeyboardUp(key);
	}
}

void Application::onMouseMove(SDL_MouseMotionEvent& mouse)
{
	if (config::isDebug) {
		cameraManager.MouseMove(mouse);
	}
}

void Application::onMouseDown(SDL_MouseButtonEvent& mouse)
{
	// nothing to do here
}

void Application::onMouseUp(SDL_MouseButtonEvent& mouse)
{
	// nothing to do here
}

void Application::onMouseWheel(SDL_MouseWheelEvent& wheel)
{
	// nothing to do here
}

void Application::onResize(int width, int height)
{
	glViewport(0, 0, width, height);
	cameraManager.Resize(width, height);
}