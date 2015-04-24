#include "Application.h"

Application::Application(void)
{
}

bool Application::onInitialize()
{
	// set the background color
	glClearColor(0.125f, 0.25f, 0.5f, 1.0f);

	glEnable(GL_DEPTH_TEST);

	// turn off back face and turn on lines for them
	glEnable(GL_CULL_FACE);
	glPolygonMode(GL_BACK, GL_LINE);

	cameraManager.SetProj(45.0f, 640.0f / 480.0f, 0.01f, 1000.0f);

	// load shaders
	shaderManager.AttachShader(GL_VERTEX_SHADER, "vertex_shader.vert");
	shaderManager.AttachShader(GL_FRAGMENT_SHADER, "fragment_shader.frag");
	if (!shaderManager.LinkProgram())
	{
		return false;
	}

	return true;
}