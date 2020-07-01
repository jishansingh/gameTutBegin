#pragma once

#include "GameWindow.h"
#include"Model.h"
#include"Brick.h"
#include "GameLevel.h"
#include"roler.h"
#include"ball.h"
class TestClass : public GameWindow {
	Model *somModel;
	GameLevel *obp;
	Roler* rol;
	Shader* shady;
	Ball* ball;
	glm::vec3 camPosition;
	float windowRatio;
public:
	TestClass(char *nameWin):GameWindow(nameWin) {
		int framebufferwidth;
		int framebufferheight;
		glfwGetFramebufferSize(window, &framebufferwidth, &framebufferheight);
		windowRatio = framebufferwidth / (float)framebufferheight;
		int noOfRows = 20;
		int noOfCol = 20;
		Brick::brick_width = (1 / (float)noOfRows) * 2;
		Brick::brick_height = (1 / (float)windowRatio) * Brick::brick_width;
		//Brick::brick_height = (1 / (float)noOfCol) * 2;
		somModel = new Model("objFile/planet/planet.obj");
		shady = new Shader("planetVertexShader.glsl", "planetFragmentShader.glsl", "");
		camPosition = glm::vec3(0.f, 0.0f, 1.0f);
		obp = new GameLevel(noOfRows, noOfCol, noOfRows / 2, noOfCol / 2);
		rol = new Roler(0.25f, 0.025f);
		ball = new Ball(0.025f, 0.025f, 0.025f);
	}
	~TestClass() {
		delete somModel;
		delete obp;
		delete rol;
		delete shady;
		delete ball;
	}
	void updateInputs() {
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
			camPosition.z -= 0.01f;
		else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			camPosition.z += 0.01f;
	}
	void updateUniforms(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale) {
		glm::vec3 worldUp(0.f, 1.f, 0.f);
		glm::vec3 camFront(0.f, 0.f, 0.f);

		glm::vec3 lightPos0(-2.0f, 10.0f, 1.0f);
		glm::mat4 modelMatrix(1.f);
		
		modelMatrix = glm::translate(modelMatrix, position);
		modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.x), glm::vec3(1.f, 0.f, 0.f));
		modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.y), glm::vec3(0.f, 1.f, 0.f));
		modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.z), glm::vec3(0.f, 0.f, 1.f));
		modelMatrix = glm::scale(modelMatrix, scale);

		//view Matrix

		updateInputs();
		glm::mat4 viewMatrix(1.f);
		glm::vec3 front = glm::cross(glm::cross(worldUp, camPosition), worldUp);
		viewMatrix = glm::lookAt(camPosition, camFront, worldUp);

		//projection matrix
		float fov = 90.f;
		float nearPlane = 0.1f;
		float farPlane = 100.f;

		glm::mat4 projectionMatrix(1.f);
		int framebufferwidth;
		int framebufferheight;
		glfwGetFramebufferSize(window, &framebufferwidth, &framebufferheight);
		//projectionMatrix = glm::perspective(glm::radians(fov), static_cast<float>(framebufferwidth) / framebufferheight, nearPlane, farPlane);
		//projectionMatrix = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, nearPlane, farPlane);
		/*float near_plane = 0.1f, far_plane = 100.5f;
		glm::mat4 projectionMatrix = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);*/

		shady->setUniform3f("camPos", GL_FALSE, camPosition);
		shady->setUniform3f("lightPos0", GL_FALSE, lightPos0);
		shady->setUniformMatrix4fv("modelMatrix", GL_FALSE, modelMatrix);
		shady->setUniformMatrix4fv("viewMatrix", GL_FALSE, viewMatrix);
		shady->setUniformMatrix4fv("projectionMatrix", GL_FALSE, projectionMatrix);

	}
	void updateMatrix() {
		glm::vec3 worldUp(0.f, 1.f, 0.f);
		glm::vec3 camFront(0.f, 0.f, 0.f);

		glm::vec3 lightPos0(-2.0f, 10.0f, 1.0f);
		//view Matrix

		updateInputs();
		glm::mat4 viewMatrix(1.f);
		glm::vec3 front = glm::cross(glm::cross(worldUp, camPosition), worldUp);
		viewMatrix = glm::lookAt(camPosition, camFront, worldUp);

		//projection matrix
		float fov = 90.f;
		float nearPlane = 0.1f;
		float farPlane = 100.f;

		glm::mat4 projectionMatrix(1.f);
		int framebufferwidth;
		int framebufferheight;
		glfwGetFramebufferSize(window, &framebufferwidth, &framebufferheight);
		//projectionMatrix = glm::perspective(glm::radians(fov), static_cast<float>(framebufferwidth) / framebufferheight, nearPlane, farPlane);
		//projectionMatrix = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, nearPlane, farPlane);
		/*float near_plane = 0.1f, far_plane = 100.5f;
		glm::mat4 projectionMatrix = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);*/

		shady->setUniformMatrix4fv("viewMatrix", GL_FALSE, viewMatrix);
		shady->setUniformMatrix4fv("projectionMatrix", GL_FALSE, projectionMatrix);
	}
	void updateInputs(glm::vec3 &position, glm::vec3& velocity) {
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
			if (velocity.x > 0)
				velocity.x = 0;
			else
				velocity.x -= 0.00001f;
		}
		else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
			if (velocity.x < 0)
				velocity.x = 0;
			else
				velocity.x += 0.00001f;
		}
	}
	void preRender() {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		shady->Use();
		updateMatrix();
		obp->detectCollision(ball);
		obp->updateModelMatrix(shady);
		obp->RenderLevel(shady);
		//somModel->Draw(shady);
		updateInputs(rol->position,rol->velocity);
		updateMatrix();
		rol->updateUniforms(shady);
		rol->Draw(shady);
		ball->detectCollision(rol);
		ball->updateUniforms(shady);
		ball->Draw(shady);

	}
	void postRender() {
	}

};
posLinkList Brick::position;
Texture* Brick::texture;
RectData Brick::somData;
unsigned int Brick::posbo;
float Brick::brick_height = 0.1f;
float Brick::brick_width = 0.1f;
int main() {
	TestClass* sompob = new TestClass((char*)"new game");
	sompob->render();
	Brick::clearData();
	delete sompob;

}