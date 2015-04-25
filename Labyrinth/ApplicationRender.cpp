#include "Application.h"

#include <iostream>

#include "config.h"

void Application::onRender()
{
	//std::cout << "[onRender()] Start" << std::endl;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	shaderManager.On();

	shaderManager.SetTexture("texture_grass", 0, grassTextureID);

	glm::mat4 matWorld;
	glm::mat4 mvp;

	// draw the grass
	for (int i = 0; i < config::MAP_SIZE; ++i) {
		for (int j = 0; j < config::MAP_SIZE; ++j) {
			matWorld = glm::translate<float>(i, 0, j);
			mvp = cameraManager.GetViewProj() * matWorld;

			shaderManager.SetUniform("MVP", mvp);

			vertexBufferManager.On();
			vertexBufferManager.Draw(GL_QUADS, 0, 4);
			vertexBufferManager.Off();
		}
	}

	shaderManager.Off();

	//std::cout << "[onRender()] End" << std::endl;
}