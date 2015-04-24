#include "Application.h"

#include "GLUtils.hpp"
#include "ObjParser_OGL3.h"

Application::Application(void)
{
	m_textureID = 0;
	m_mesh = 0;
}

bool Application::initialize()
{
	// set the background color
	glClearColor(0.125f, 0.25f, 0.5f, 1.0f);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glPolygonMode(GL_BACK, GL_LINE);

	//
	// geometria letrehozasa
	//
	m_vb.AddAttribute(0, 3); //p
	m_vb.AddAttribute(1, 3); //n
	m_vb.AddAttribute(2, 2); //tex

	m_vb.AddData(0, -10, 0, -10); // 0. v-nek a pos-ja
	m_vb.AddData(0, 10, 0, -10); // 1. v-nek a pos-ja
	m_vb.AddData(0, -10, 0, 10);
	m_vb.AddData(0, 10, 0, 10);

	m_vb.AddData(1, 0, 1, 0); // 0. v-nek a pos-ja
	m_vb.AddData(1, 0, 1, 0); // 1. v-nek a pos-ja
	m_vb.AddData(1, 0, 1, 0);
	m_vb.AddData(1, 0, 1, 0);

	m_vb.AddData(2, 0, 0);
	m_vb.AddData(2, 1, 0);
	m_vb.AddData(2, 0, 1);
	m_vb.AddData(2, 1, 1);

	m_vb.AddIndex(1, 0, 2); // index puffer
	m_vb.AddIndex(1, 2, 3);

	m_vb.InitBuffers();

	//
	// shaderek betöltése
	//
	m_program.AttachShader(GL_VERTEX_SHADER, "vertex_shader.vert");
	m_program.AttachShader(GL_FRAGMENT_SHADER, "fragment_shader.frag");

	m_program.BindAttribLoc(0, "vs_in_pos");
	m_program.BindAttribLoc(1, "vs_in_normal");
	m_program.BindAttribLoc(2, "vs_in_tex0");

	if (!m_program.LinkProgram())
	{
		return false;
	}

	//
	// egyéb inicializálás
	//

	m_camera.SetProj(45.0f, 640.0f / 480.0f, 0.01f, 1000.0f);

	// textúra betöltése
	m_textureID = TextureFromFile("texture.png");

	// mesh betöltés
	m_mesh = ObjParser::parse("suzanne.obj");
	m_mesh->initBuffers();

	return true;
}