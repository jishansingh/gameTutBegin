#pragma once
#include"libs.h"
#include"Shader.h"
class RectData {
public:
	unsigned int vao;
	unsigned int vbo;
	unsigned int ibo;
	RectData() {
	}
	void initRectData(){
		float vertices_box[12]{
			-0.5f, 0.5f,0.f,
			-0.5f,-0.5f,0.f,
			 0.5f,-0.5f,0.f,
			 0.5f, 0.5f,0.f,
		};
		GLuint indVert[] = {
			2,1,0,
			3,2,0
		};
		glBindVertexArray(0);
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(float), &vertices_box[0], GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
		glEnableVertexAttribArray(0);

		glGenBuffers(1, &ibo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(GLuint), indVert, GL_STATIC_DRAW);
	}
};

class Brick {
public:
	static std::vector<glm::vec2> position;
	static RectData somData;
	static unsigned int posbo;
	Brick(int x,int y,int row,int col) {
		float unitStepX = row / 2;
		float normIndexX = (x - unitStepX) / unitStepX;
		float unitStepY = col / 2;
		float normIndexY = (x - unitStepY) / unitStepY;
		glm::vec2 posFin(normIndexX, normIndexY);
		position.push_back(posFin);
	}
	static void initData() {
		somData.initRectData();
		glBindVertexArray(somData.vao);
		glGenBuffers(1, &posbo);
		glBindBuffer(GL_ARRAY_BUFFER, posbo);
		glBufferData(GL_ARRAY_BUFFER, position.size() *2* sizeof(float), &position[0], GL_STATIC_DRAW);
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, posbo);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glVertexAttribDivisor(1, 1);
	}
	static void Draw(Shader* shady) {
		shady->Use();
		glBindVertexArray(somData.vao);
		glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0, position.size());
	}

};

