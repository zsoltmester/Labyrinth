#include "Application.h"

#include <iostream>

#include "GLUtils.hpp"

//
// Helper functions
//

void createQuad(gVertexBuffer &vertexBufferManager, GLuint &grassTextureID)
{
	vertexBufferManager.AddAttribute(0, 3); // position
	vertexBufferManager.AddAttribute(1, 3); // normal
	vertexBufferManager.AddAttribute(2, 2); // texture

	// position                     x  y   z
	vertexBufferManager.AddData(0, 1, 0, 1); // lower right
	vertexBufferManager.AddData(0, 1, 0, -1); // upper right
	vertexBufferManager.AddData(0, -1, 0, -1); // upper left
	vertexBufferManager.AddData(0, -1, 0, 1); // lower left

	// normal                      x  y  z
	vertexBufferManager.AddData(1, 0, 1, 0);
	vertexBufferManager.AddData(1, 0, 1, 0);
	vertexBufferManager.AddData(1, 0, 1, 0);
	vertexBufferManager.AddData(1, 0, 1, 0);

	// texture
	vertexBufferManager.AddData(2, 0, 0);
	vertexBufferManager.AddData(2, 1, 0);
	vertexBufferManager.AddData(2, 0, 1);
	vertexBufferManager.AddData(2, 1, 1);

	vertexBufferManager.InitBuffers();

	grassTextureID = TextureFromFile("texture_grass.jpg");
}

//
// Application's functions
//

Application::Application(void)
{
}

bool Application::onInitialize()
{
	//std::cout << "[onInitialize()] Start" << std::endl;

	// set the background color
	glClearColor(0.125f, 0.25f, 0.5f, 1.0f);

	glEnable(GL_DEPTH_TEST);

	// turn off back face and turn on lines for them
	glEnable(GL_CULL_FACE);
	glPolygonMode(GL_BACK, GL_LINE);

	createQuad(vertexBufferManager, grassTextureID);

	// load shaders
	shaderManager.AttachShader(GL_VERTEX_SHADER, "vertex_shader.vert");
	shaderManager.AttachShader(GL_FRAGMENT_SHADER, "fragment_shader.frag");
	shaderManager.BindAttribLoc(0, "vs_in_position");
	shaderManager.BindAttribLoc(2, "vs_in_texture_grass");
	if (!shaderManager.LinkProgram())
	{
		return false;
	}

	cameraManager.SetProj(45.0f, 640.0f / 480.0f, 0.01f, 1000.0f);

	//std::cout << "[onInitialize()] End" << std::endl;

	return true;
}