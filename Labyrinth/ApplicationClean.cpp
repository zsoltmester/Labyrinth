#include "Application.h"

Application::~Application(void)
{
}

void Application::onClean()
{
	glDeleteTextures(1, &grassTextureID);
	glDeleteTextures(1, &wallTextureID);
	glDeleteTextures(1, &coinTextureID);
	glDeleteTextures(1, &diamondTextureID);
	glDeleteTextures(1, &suzanneTextureID);
	shaderManager.Clean();
}