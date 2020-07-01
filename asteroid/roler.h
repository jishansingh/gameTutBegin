#pragma once
#include"libs.h"
#include"Shader.h"
class Roler {
	unsigned int vao;
	unsigned int vbo;
	unsigned int ibo;
public:
	float rolWidth;
	float rolHeight;
	glm::vec3 position;
	Roler(float width, float height) {
		position = glm::vec3(0.f, -1.f, 0.f);
		float offset = 0.0f;
		float vertices_box[12]{
			-width + offset, height - offset,0.f,
			-width + offset,-height + offset,0.f,
			 width - offset,-height + offset,0.f,
			 width - offset, height - offset,0.f,
		};
		rolWidth = width;
		rolHeight = height;
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
	
	void Draw(Shader* shady) {
		shady->Use();
		glBindVertexArray(vao);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}

	void updateUniforms(Shader*shady) {
		glm::vec3 worldUp(0.f, 1.f, 0.f);
		glm::vec3 camFront(0.f, 0.f, 0.f);

		glm::vec3 lightPos0(-2.0f, 10.0f, 1.0f);
		glm::mat4 modelMatrix(1.f);

		modelMatrix = glm::translate(modelMatrix, position);
		modelMatrix = glm::scale(modelMatrix, glm::vec3(1.f));
		shady->setUniformMatrix4fv("modelMatrix", GL_FALSE, modelMatrix);

	}

};
