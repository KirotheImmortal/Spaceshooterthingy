#pragma once
#include "SystemDef.h"
#include "crenderutils.h"

sysDef(Rendering)

bool init() { return true; }
bool term() { return true; }

bool condition(Entity *e)
{
	return e->active && e->render && e->transform;
}

void update(Entity *e)
{
	auto &r = *e->render;
	auto &t = *e->transform;
	auto &assets = core(Asset);
	auto &camera = core(Camera).getCamera();


	auto mesh   = assets.getMesh(r.mesh);
	auto shader = assets.getShader(r.shader);
	auto texture = assets.getTexture(r.texture);
	
	r.frame = r.frame * r.frameRate;
	r.frame += core(Time).getDeltaTime();
	
	if (r.frame > texture.rows * texture.cols)
		r.frame = 0;


	glUseProgram(shader);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	///////////////////////////////////////////textureShader.frag///////////////////////////////////////////
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture.handle);
	GLuint ul_texture = glGetUniformLocation(shader, "Diffuse");
	glUniform1i(ul_texture, 0);

	GLuint ul_rows = glGetUniformLocation(shader, "Rows");
	GLuint ul_cols = glGetUniformLocation(shader, "Cols");
	GLuint ul_frame = glGetUniformLocation(shader, "Frame");
	glUniform1i(ul_rows, texture.rows);
	glUniform1i(ul_cols, texture.cols);
	glUniform1i(ul_frame, r.frame);

	////////////////////////////////////////////////////////////////////////////////////////////////
	GLuint ul_view	= glGetUniformLocation(shader, "View");
	GLuint ul_model = glGetUniformLocation(shader, "Model");
	GLuint ul_proj	= glGetUniformLocation(shader, "Projection");

	glUniformMatrix4fv(ul_proj,	 1, GL_FALSE, camera.projection.m);
	glUniformMatrix4fv(ul_view,  1, GL_FALSE, camera.view.m);
	glUniformMatrix4fv(ul_model, 1, GL_FALSE, t.m_global.m);
	


	glBindVertexArray(mesh.VAO);
	glDrawElements(GL_TRIANGLES, mesh.size, GL_UNSIGNED_INT, NULL);

	glBindVertexArray(0);
	glUseProgram(0);	
}


sysEndDef