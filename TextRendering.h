#pragma once
#include "SystemDef.h"
#include "crenderutils.h"

sysDef(TextRendering)


bool init() {return true;}
bool term() {return true;}

bool condition(Entity *e)
{
	return e->active && e->textrender && e->transform;
}

void update(Entity *e)
{
	auto &r = *e->textrender;
	auto &t = *e->transform;
	auto &assets = core(Asset);
	auto &camera = core(Camera).getCamera();


	auto mesh = assets.getMesh("font");
	auto shader = assets.getShader("Texture");
	auto texture = assets.getTexture("TextFont");



	glUseProgram(shader);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	/////////////////////////////////////////textureShader.frag///////////////////////////////////////////
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture.handle);
	GLuint ul_texture = glGetUniformLocation(shader, "Diffuse");
	glUniform1i(ul_texture, 0);

	GLuint ul_rows = glGetUniformLocation(shader, "Rows");
	GLuint ul_cols = glGetUniformLocation(shader, "Cols");
	GLuint ul_frame = glGetUniformLocation(shader, "Frame");
	glUniform1i(ul_rows, texture.rows);
	glUniform1i(ul_cols, texture.cols);
	//////////////////////////////////////////////////////////////////////////////////////////////
	GLuint ul_view = glGetUniformLocation(shader, "View");
	GLuint ul_model = glGetUniformLocation(shader, "Model");
	GLuint ul_proj = glGetUniformLocation(shader, "Projection");

	glUniformMatrix4fv(ul_proj, 1, GL_FALSE, camera.projection.m);
	glUniformMatrix4fv(ul_view, 1, GL_FALSE, camera.view.m);
	glBindVertexArray(mesh.VAO);

	for (int i = 0; i < e->textrender->text.length(); i++)
	{
		vec3 offset = { i*20, i * -20, 0 };
		glUniformMatrix4fv(ul_model, 1, GL_FALSE,(makeTranslation(offset) * t.m_global).m);
		glUniform1i(ul_frame, e->textrender->text[i]);
		
		glDrawElements(GL_TRIANGLES, mesh.size, GL_UNSIGNED_INT, NULL);
	}
	
	

	glBindVertexArray(0);
	glUseProgram(0);
}

	sysEndDef
