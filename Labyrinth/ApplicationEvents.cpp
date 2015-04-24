#include "Application.h"

void Application::onKeyboardDown(SDL_KeyboardEvent& key)
{
	cameraManager.KeyboardDown(key);
}

void Application::onKeyboardUp(SDL_KeyboardEvent& key)
{
	cameraManager.KeyboardUp(key);
}

void Application::onMouseMove(SDL_MouseMotionEvent& mouse)
{
	// TODO only for DEBUG
	cameraManager.MouseMove(mouse);
}

void Application::onMouseDown(SDL_MouseButtonEvent& mouse)
{
}

void Application::onMouseUp(SDL_MouseButtonEvent& mouse)
{
}

void Application::onMouseWheel(SDL_MouseWheelEvent& wheel)
{
}

void Application::onResize(int width, int height)
{
	glViewport(0, 0, width, height);
	cameraManager.Resize(width, height);
}