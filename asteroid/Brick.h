#pragma once
#include"libs.h"
#include"Shader.h"
#include"ball.h"
class RectData {
public:
	unsigned int vao;
	unsigned int vbo;
	unsigned int ibo;
	RectData() {
	}
	void initRectData(float width,float height){
		float offset = 0.06f;
		float vertices_box[12]{
			-width + offset, height - offset,0.f,
			-width + offset,-height + offset,0.f,
			 width - offset,-height + offset,0.f,
			 width - offset, height - offset,0.f,
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
	~RectData() {
		glDeleteBuffers(1, &vbo);
		glDeleteBuffers(1, &ibo);
		glDeleteVertexArrays(1, &vao);

	}
};

class Brick {
public:
	static std::vector<glm::vec2> position;
	static RectData somData;
	static unsigned int posbo;
	static float brick_width;
	static float brick_height;
	Brick(int x,int y,int row,int col) {
		float unitStepX = row / (float)2;
		float normIndexX = (x - unitStepX) / (float)unitStepX;
		float unitStepY = col / (float)2;
		float normIndexY = (y - unitStepY) / (float)unitStepY;
		glm::vec2 posFin = glm::vec2(normIndexX, normIndexY);
		position.push_back(posFin);
	}
	static void initData() {
		somData.initRectData(brick_width, brick_height);
		glBindVertexArray(somData.vao);
		glGenBuffers(1, &posbo);
		glBindBuffer(GL_ARRAY_BUFFER, posbo);
		glBufferData(GL_ARRAY_BUFFER, position.size() * sizeof(glm::vec2), position.data(), GL_STATIC_DRAW);
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, posbo);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void*)0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glVertexAttribDivisor(1, 1);
	}
	static void Draw(Shader* shady) {
		shady->Use();
		glBindVertexArray(somData.vao);
		glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0, position.size());
	}
	static bool checkOverlap(glm::vec2 vector1, glm::vec2 vector2) {
		if (abs(vector1.x - vector2.x) < 2 * brick_width && (abs(vector1.y - vector2.y) < 2 * brick_height)) {
			return true;
		}
		return false;
	}
	static void detectCollision(Ball* ball) {
		std::vector<std::vector<glm::vec2>::iterator> itArr;
		for (auto it = position.begin(); it!= position.end(); it++) {
			if (checkOverlap(*it, glm::vec2(ball->position.x, ball->position.y))) {
				itArr.push_back(it);
			}
		}
		for (int i = 0; i < itArr.size(); i++) {
			position.erase(itArr[i]);
		}
	}
	~Brick() {
		glDeleteBuffers(1, &posbo);
	}
};

