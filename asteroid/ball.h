#pragma once
#include"libs.h"
#include"Shader.h"
#include"roler.h"
class Ball {
	unsigned int vao;
	unsigned int vbo;
	unsigned int ibo;
	Texture* texture;
	glm::vec2 velocity;
public:
	glm::vec3 position;
	Ball(float width, float height,float rolHeight) {
		texture = new Texture("objfile/awesomeface.png", GL_TEXTURE_2D, 1);
		position = glm::vec3(0.f, -1.f+ 2*rolHeight, 0.f);
		float offset = 0.0f;
		velocity = glm::vec2(0.001f, 0.001f);
		float vertices_box[16]{
			-width + offset, height - offset,0.f,1.f,
			-width + offset,-height + offset,0.f,0.f,
			 width - offset,-height + offset,1.f,0.f,
			 width - offset, height - offset,1.f,1.f
		};
		unsigned int noOfVertices = sizeof(vertices_box) / (4 * sizeof(float));
		GLuint indVert[] = {
			2,1,0,
			3,2,0
		};
		glBindVertexArray(0);
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, noOfVertices * 4 * sizeof(float), &vertices_box[0], GL_STATIC_DRAW);

		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
		glEnableVertexAttribArray(0);

		glGenBuffers(1, &ibo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(GLuint), indVert, GL_STATIC_DRAW);
	}
	void updateUniforms(Shader* shady) {
		position += glm::vec3(velocity, 0.f);
		if (position.x < -1.f|| position.x > 1.f){
			velocity.x = -velocity.x;
		}
		if (position.y > 1.f) {
			velocity.y = -velocity.y;
		}

		glm::vec3 worldUp(0.f, 1.f, 0.f);
		glm::vec3 camFront(0.f, 0.f, 0.f);

		glm::vec3 lightPos0(-2.0f, 10.0f, 1.0f);
		glm::mat4 modelMatrix(1.f);

		//modelMatrix = glm::translate(modelMatrix, position);
		modelMatrix = glm::scale(modelMatrix, glm::vec3(1.f));
		shady->setUniformMatrix4fv("modelMatrix", GL_FALSE, modelMatrix);

	}
	void detectCollision(Roler* roler) {
		if ((roler->position.x - roler->rolWidth) < position.x&& (roler->position.x + roler->rolWidth) > position.x && abs(position.y + 1.f) < 0.01f) {
			velocity.y = -velocity.y;
		}
	}
	void changeVelY() {
		velocity.y = -velocity.y;
	}
	void Draw(Shader* shady) {
		shady->Use();
		glm::vec2 temp = glm::vec2(position.x, position.y);
		shady->setUniform2f("offsets[0]", temp);
		texture->bind();
		shady->setUniform1i("texture0", texture->getTextureUnit());
		glBindVertexArray(vao);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}
};
