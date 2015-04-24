#include "Application.h"

void Application::keyboardDown(SDL_KeyboardEvent& key)
{
	m_camera.KeyboardDown(key);
}

void Application::keyboardUp(SDL_KeyboardEvent& key)
{
	m_camera.KeyboardUp(key);
}

void Application::mouseMove(SDL_MouseMotionEvent& mouse)
{
	m_camera.MouseMove(mouse);
}

void Application::mouseDown(SDL_MouseButtonEvent& mouse)
{
}

void Application::mouseUp(SDL_MouseButtonEvent& mouse)
{
}

void Application::mouseWheel(SDL_MouseWheelEvent& wheel)
{
}

// a két paraméterbe az új ablakméret szélessége (_w) és magassága (_h) található
void Application::resize(int _w, int _h)
{
	glViewport(0, 0, _w, _h);

	m_camera.Resize(_w, _h);
}