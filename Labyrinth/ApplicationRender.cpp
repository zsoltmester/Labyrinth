#include "Application.h"

#include <iostream>

void Application::onRender()
{
	//std::cout << "[onRender()] Start" << std::endl;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	shaderManager.On();

	glm::mat4 matWorld = glm::mat4(1.0f);
	glm::mat4 mvp = cameraManager.GetViewProj() * matWorld;
	shaderManager.SetUniform("MVP", mvp);
	shaderManager.SetTexture("texture_grass", 0, grassTextureID);
	
	vertexBufferManager.On();
	vertexBufferManager.Draw(GL_QUADS, 0, 4);
	vertexBufferManager.Off();

	shaderManager.Off();

	//std::cout << "[onRender()] End" << std::endl;
}