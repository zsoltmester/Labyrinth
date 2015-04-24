#include "Application.h"

Application::~Application(void)
{
}

void Application::onClean()
{
	shaderManager.Clean();
}