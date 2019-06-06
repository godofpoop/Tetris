#include "RenderSystem.h"
#include "Shape.h"
#include "TetrisGame.h"

RenderSystem::RenderSystem()
{
}
void RenderSystem::init()
{
	shader = Shader("shaders/shader");
	guiShader = Shader("shaders/gui");
	numberShader = Shader("shaders/number");
	texture = new Texture("res/block.png");
	numberTexture = new Texture("res/numbers.png");
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glEnableVertexAttribArray(0);

	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 12, &vertices[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);


	glBindVertexArray(0);
	glDisableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
void RenderSystem::update()
{
	shader.bind();
	glBindVertexArray(vao);
	glEnableVertexAttribArray(0);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture->texture_id);
	shader.setUniform("sampler", 0);
	for (int i = 0; i < entities.size(); i++) {
		
 		shader.setUniform("custom_color", entities[i]->color);
		shader.setUniform("transformation", maths::createTransformationMatrix(vector3(entities[i]->position.x, entities[i]->position.y, 0.0), vector3(), vector3(10)));
		shader.setUniform("projection", maths::ortho(0, 400, 150, 550, -1, 1));
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}
	glDisableVertexAttribArray(0);
	glBindVertexArray(0);
	shader.unBind();
	drawNumber();
	drawGui();
}
void RenderSystem::addEntity(Entity* e)
{
	entities.push_back(e);
}
void RenderSystem::addEntity(Shape* e)
{
	for (int i = 0; i < e->entities.size(); i++) {
		entities.push_back(e->entities[i]);
	}
}
void RenderSystem::remove(Shape& e)
{
	for (int i = 0; i < entities.size(); i++) {
		for (int j = 0; j < e.entities.size(); j++) {
			if (e.entities[j] == entities[i]) {
				entities.erase(entities.begin() + i);
			}
		}
	}
}
void RenderSystem::remove(Entity* e) {
	for (int i = 0; i < entities.size(); i++) {
		if (entities[i] == e) {
			entities.erase(entities.begin() + i);
			
			return;
		}
	}
}
void RenderSystem::addGui(Gui& g)
{
	guis.push_back(&g);
}
void RenderSystem::drawGui()
{
	guiShader.bind();
	glBindVertexArray(vao);
	glEnableVertexAttribArray(0);

	
	guiShader.setUniform("sampler", 0);
	for (int i = 0; i < guis.size(); i++) {
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, guis[i]->texture->texture_id);
		guiShader.setUniform("transformation", maths::createTransformationMatrix(vector3(guis[i]->position.x, guis[i]->position.y, guis[i]->depth), vector3(), vector3(guis[i]->scale.x,guis[i]->scale.y,0.0)));
		guiShader.setUniform("projection", maths::ortho(0, 400, 150, 550, -1, 1));
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}
	glDisableVertexAttribArray(0);
	glBindVertexArray(0);
	guiShader.unBind();
}
void RenderSystem::addNumber(const vector2 &p,int& i)
{
	numbers.push_back(&i);
	pos.push_back(p);
	
}
int length(int num) {
	int res = 0;
	int tmp = num; 
	while (tmp > 1) {
		tmp = tmp / 10;
		res++;
	}
	return res;
}
void RenderSystem::drawNumber()
{
	number = TetrisGame::score;
	numberShader.bind();
	glBindVertexArray(vao);
	glEnableVertexAttribArray(0);


	numberShader.setUniform("sampler", 0);
	for (int k = 0; k < numbers.size(); k++) {
		int j = 0;
		for (int i = *numbers[k]; i >= 1; i /= 10.f) {
			j++;
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, numberTexture->texture_id);
			numberShader.setUniform("row", i % 10);
			numberShader.setUniform("transformation", maths::createTransformationMatrix(vector3(pos[k].x - j * 16 + length(*numbers[k])*8, pos[k].y, 0.0), vector3(), vector3(8, 8, 1)));
			numberShader.setUniform("projection", maths::ortho(0, 400, 150, 550, -1, 1));
			glDrawArrays(GL_TRIANGLES, 0, 6);
		}
		if (*numbers[k] == 0) {
			for (int i = 0; i < 4; i++) {
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, numberTexture->texture_id);
				numberShader.setUniform("row", 0);
				numberShader.setUniform("transformation", maths::createTransformationMatrix(vector3(pos[k].x - i * 16, pos[k].y, 0.0), vector3(), vector3(8, 8, 1)));
				numberShader.setUniform("projection", maths::ortho(0, 400, 150, 550, -1, 1));
				glDrawArrays(GL_TRIANGLES, 0, 6);
			}
		}
	}
	
	glDisableVertexAttribArray(0);
	glBindVertexArray(0);
	numberShader.unBind();
}
RenderSystem::~RenderSystem()
{
}
