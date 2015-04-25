#include "Application.h"

Application::~Application(void)
{
}

void Application::onClean()
{
	glDeleteTextures(1, &grassTextureID);
	shaderManager.Clean();
}