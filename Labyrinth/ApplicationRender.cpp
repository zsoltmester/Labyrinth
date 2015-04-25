#include "Application.h"

#include <iostream>

#include "config.h"

void Application::onRender()
{
	//std::cout << "[onRender()] Start" << std::endl;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	shaderManager.On();

	glm::mat4 matWorld;
	glm::mat4 mvp;

	// draw the grass
	for (int i = 0; i < config::MAP_SIZE; ++i) {
		for (int j = 0; j < config::MAP_SIZE; ++j) {
			matWorld = glm::translate<float>(i, 0, j);
			mvp = cameraManager.GetViewProj() * matWorld;
			shaderManager.SetUniform("MVP", mvp);

			if (i == 0 && j == 0) // TODO temp
			{
				shaderManager.SetTexture("texture_image", 0, grassTextureID);

				vertexBufferManager.On();
				vertexBufferManager.Draw(GL_QUADS, 0, 4);

				shaderManager.SetTexture("texture_image", 0, wallTextureID);

				// left
				//matWorld = matWorld;

				// right
				//matWorld = matWorld * glm::translate<float>(0, 0, config::QUAD_SIDE - config::WALL_THICKNESS);

				// lower
				//matWorld = matWorld 
				//	* glm::translate<float>(config::WALL_THICKNESS, 0, 0)
				//	* glm::rotate<float>(-90, 0, 1, 0);
				
				// upper
				//matWorld = matWorld
				//	* glm::translate<float>(config::QUAD_SIDE, 0, 0)
				//	* glm::rotate<float>(-90, 0, 1, 0);


				mvp = cameraManager.GetViewProj() * matWorld;
				shaderManager.SetUniform("MVP", mvp);
				vertexBufferManager.Draw(GL_QUADS, 4, 20);
			}
			vertexBufferManager.Off();
		}
	}

	shaderManager.Off();

	//std::cout << "[onRender()] End" << std::endl;
}