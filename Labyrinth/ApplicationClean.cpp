#include "Application.h"

Application::~Application(void)
{
}

void Application::clean()
{
	glDeleteTextures(1, &m_textureID);

	m_program.Clean();
}