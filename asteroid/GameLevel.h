#pragma once
#include"libs.h"
#include"Brick.h"

class GameLevel {
	std::vector<Brick*> allBricks;
public:
	GameLevel(int rows, int cols, int width, int height) {
		for (int i = rows-1; i > rows - width; i--) {
			for (int j = 0; j < cols; j++) {
				allBricks.push_back(new Brick(j, i, rows, cols));
			}
		}
		allBricks[0]->initData();
	}
	void RenderLevel(Shader* shady) {
		Brick::Draw(shady);
	}
	~GameLevel(){
		for (int i = 0; i < allBricks.size(); i++) {
			delete allBricks[i];
		}
	}
	void detectCollision(Ball* ball) {
		Brick::detectCollision(ball);
	}
	void updateModelMatrix(Shader* shady) {
		glm::mat4 modelMatrix(1.f);
		modelMatrix = glm::scale(modelMatrix, glm::vec3(1.f));
		shady->setUniformMatrix4fv("modelMatrix", GL_FALSE, modelMatrix);
	}
};