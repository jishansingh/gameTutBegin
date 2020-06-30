#include"libs.h"
#include"Shader.h"
#include"Texture.h"
#include"Mesh.h"
#include"Model.h"
#include"frameBuffer.h"

void framebuffer_resize_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

float vertices_box[] = {
	-0.5f,0.f, 0.5f,
	-0.5f,0.f,-0.5f,
	 0.5f,0.f,-0.5f,
	 0.5f,0.f, 0.5f,
};

float normal[] = {
	0.f,1.f,0.f,
	0.f,1.f,0.f,
	0.f,1.f,0.f,
	0.f,1.f,0.f,
};

float texcoord[] = {
	0.f,1.f,
	0.f,0.f,
	1.f,0.f,
	1.f,1.f,
};

Vertex vertex_box[] = {
	glm::vec3()   ,glm::vec3(0.f,0.f,1.f),glm::vec2(0.f,1.f),
	glm::vec3() ,glm::vec3(0.f,0.f,1.f),glm::vec2(0.f,0.f),
	glm::vec3()  ,glm::vec3(0.f,0.f,1.f),glm::vec2(1.f,0.f),
	glm::vec3()   ,glm::vec3(0.f,0.f,1.f),glm::vec2(1.f,1.f),
};

float quadVertices[] = { // vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
		// positions   // texCoords
		-1.0f,  1.0f,0.f,  0.0f, 1.0f,
		-1.0f, -1.0f,0.f,  0.0f, 0.0f,
		 1.0f, -1.0f,0.f,  1.0f, 0.0f,

		-1.0f,  1.0f,0.f,  0.0f, 1.0f,
		 1.0f, -1.0f,0.f,  1.0f, 0.0f,
		 1.0f,  1.0f,0.f,  1.0f, 1.0f
};
unsigned int noOfBoxVertices2 = sizeof(quadVertices) / (5 * sizeof(float));
unsigned int noOfBoxVertices = sizeof(vertices_box) / (3 * sizeof(float));

GLuint indices[] = {
	2,1,0,
	3,2,0
};
unsigned int noOfIndices = sizeof(indices) / sizeof(GLuint);
/*
float vertices[] = {
	-0.5f, -0.5f, -0.5f,-1.f,-1.f, -1.f,   0.0f,  0.0f, -1.0f,
	 0.5f, -0.5f, -0.5f, 1.f,-1.f, -1.f,   0.0f,  0.0f, -1.0f,
	 0.5f,  0.5f, -0.5f, 1.f, 1.f, -1.f,   0.0f,  0.0f, -1.0f,
	 0.5f,  0.5f, -0.5f, 1.f, 1.f, -1.f,   0.0f,  0.0f, -1.0f,
	-0.5f,  0.5f, -0.5f,-1.f, 1.f, -1.f,  0.0f,  0.0f, -1.0f,
	-0.5f, -0.5f, -0.5f,-1.f,-1.f, -1.f,  0.0f,  0.0f, -1.0f,

	-0.5f, -0.5f,  0.5f,-1.f,-1.f, 1.f, 0.0f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f, 1.f,-1.f, 1.f, 0.0f,  0.0f, 1.0f,
	 0.5f,  0.5f,  0.5f, 1.f, 1.f, 1.f, 0.0f,  0.0f, 1.0f,
	 0.5f,  0.5f,  0.5f, 1.f, 1.f, 1.f, 0.0f,  0.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,-1.f, 1.f, 1.f, 0.0f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,-1.f,-1.f, 1.f, 0.0f,  0.0f, 1.0f,

	-0.5f,  0.5f,  0.5f,-1.f, 1.f, 1.f,	  -1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f, -0.5f,-1.f, 1.f, -1.f,  -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,-1.f, -1.f, -1.f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,-1.f, -1.f, -1.f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f,  0.5f,-1.f, -1.f, 1.f,  -1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f,  0.5f,-1.f, 1.f, 1.f,	  -1.0f,  0.0f,  0.0f,

	 0.5f,  0.5f,  0.5f,1.f, 1.f, 1.f,	   1.0f,  0.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,1.f, 1.f, -1.f,	   1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,1.f, -1.f, -1.f,   1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,1.f, -1.f, -1.f,   1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,1.f, -1.f, 1.f,	   1.0f,  0.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,1.f, 1.f, 1.f,	   1.0f,  0.0f,  0.0f,

	-0.5f, -0.5f, -0.5f,-1.f, -1.f, -1.f,  0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,1.f, -1.f, -1.f,   0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,1.f, -1.f, 1.f,	   0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,1.f, -1.f, 1.f,	   0.0f, -1.0f,  0.0f,
	-0.5f, -0.5f,  0.5f,-1.f, -1.f, 1.f,   0.0f, -1.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,-1.f, -1.f, -1.f,  0.0f, -1.0f,  0.0f,

	-0.5f,  0.5f, -0.5f,-1.f, 1.f, -1.f,    0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,1.f, 1.f, -1.f,	    0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,1.f, 1.f, 1.f,	    0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,1.f, 1.f, 1.f,	    0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f,  0.5f,-1.f, 1.f, 1.f,	    0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f, -0.5f,-1.f, 1.f, -1.f,    0.0f,  1.0f,  0.0f
};*/


float vertices[] = {
	// back face
	-1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f, // bottom-left
	 1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f, // top-right
	 1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 0.0f, // bottom-right         
	 1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f, // top-right
	-1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f, // bottom-left
	-1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 1.0f, // top-left
	// front face
	-1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f, // bottom-left
	 1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 0.0f, // bottom-right
	 1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f, // top-right
	 1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f, // top-right
	-1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 1.0f, // top-left
	-1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f, // bottom-left
	// left face
	-1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-right
	-1.0f,  1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 1.0f, // top-left
	-1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-left
	-1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-left
	-1.0f, -1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 0.0f, // bottom-right
	-1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-right
	// right face
	 1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-left
	 1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-right
	 1.0f,  1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 1.0f, // top-right         
	 1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-right
	 1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-left
	 1.0f, -1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 0.0f, // bottom-left     
	// bottom face
	-1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f, // top-right
	 1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 1.0f, // top-left
	 1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f, // bottom-left
	 1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f, // bottom-left
	-1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 0.0f, // bottom-right
	-1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f, // top-right
	// top face
	-1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f, // top-left
	 1.0f,  1.0f , 1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f, // bottom-right
	 1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 1.0f, // top-right     
	 1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f, // bottom-right
	-1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f, // top-left
	-1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f  // bottom-left        
};

unsigned int noOfVertices = sizeof(vertices) / (8 * sizeof(float));

void updateUniforms(GLFWwindow* window, Shader& shader, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, glm::vec3 camPosition, glm::vec3 lightPos0,
	glm::vec3 camFront, glm::vec3 worldUp) {
	glm::mat4 modelMatrix(1.f);
	modelMatrix = glm::translate(modelMatrix, position);
	modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.x), glm::vec3(1.f, 0.f, 0.f));
	modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.y), glm::vec3(0.f, 1.f, 0.f));
	modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.z), glm::vec3(0.f, 0.f, 1.f));
	modelMatrix = glm::scale(modelMatrix, scale);

	//view Matrix



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
	projectionMatrix = glm::perspective(glm::radians(fov), static_cast<float>(framebufferwidth) / framebufferheight, nearPlane, farPlane);
	//projectionMatrix = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, nearPlane, farPlane);
	/*float near_plane = 0.1f, far_plane = 100.5f;
	glm::mat4 projectionMatrix = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);*/

	shader.setUniform3f("camPos", GL_FALSE, camPosition);
	shader.setUniform3f("lightPos0", GL_FALSE, lightPos0);
	shader.setUniformMatrix4fv("modelMatrix", GL_FALSE, modelMatrix);
	shader.setUniformMatrix4fv("viewMatrix", GL_FALSE, viewMatrix);
	shader.setUniformMatrix4fv("projectionMatrix", GL_FALSE, projectionMatrix);

	//float near_plane = 0.1f, far_plane = 100.5f;

	viewMatrix = glm::lookAt(lightPos0,
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f));

	//projectionMatrix = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, nearPlane, farPlane);

	projectionMatrix = projectionMatrix * viewMatrix;
	shader.setUniformMatrix4fv("lightMatrix", GL_FALSE, projectionMatrix);

}

void updateShadow(GLFWwindow* window, Shader& shader, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, glm::vec3 camPosition, glm::vec3 lightPos0,
	glm::vec3 camFront, glm::vec3 worldUp) {
	glm::mat4 modelMatrix(1.f);
	modelMatrix = glm::translate(modelMatrix, position);
	modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.x), glm::vec3(1.f, 0.f, 0.f));
	modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.y), glm::vec3(0.f, 1.f, 0.f));
	modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.z), glm::vec3(0.f, 0.f, 1.f));
	modelMatrix = glm::scale(modelMatrix, scale);

	//view Matrix



	glm::mat4 viewMatrix(1.f);
	glm::vec3 front = glm::cross(glm::cross(worldUp, camPosition), worldUp);
	viewMatrix = glm::lookAt(lightPos0,
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f));
	//viewMatrix = glm::lookAt(camPosition, camFront, worldUp);


	//projection matrix

	float fov = 90.f;
	float nearPlane = 0.1f;
	float farPlane = 100.f;
	/*glm::mat4 projectionMatrix(1.f);
	int framebufferwidth;
	int framebufferheight;
	glfwGetFramebufferSize(window, &framebufferwidth, &framebufferheight);
	projectionMatrix = glm::perspective(glm::radians(fov), static_cast<float>(framebufferwidth) / framebufferheight, nearPlane, farPlane);*/

	glm::mat4 projectionMatrix(1.f);
	int framebufferwidth;
	int framebufferheight;
	glfwGetFramebufferSize(window, &framebufferwidth, &framebufferheight);
	projectionMatrix = glm::perspective(glm::radians(fov), 1.f, nearPlane, farPlane);

	/*float near_plane = 0.1f, far_plane = 100.5f;
	glm::mat4 projectionMatrix = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);*/

	shader.setUniform3f("camPos", GL_FALSE, camPosition);
	shader.setUniform3f("lightPos0", GL_FALSE, lightPos0);
	shader.setUniformMatrix4fv("modelMatrix", GL_FALSE, modelMatrix);
	shader.setUniformMatrix4fv("viewMatrix", GL_FALSE, viewMatrix);
	shader.setUniformMatrix4fv("projectionMatrix", GL_FALSE, projectionMatrix);

	std::vector<glm::mat4> shadowTransforms;
	shadowTransforms.push_back(projectionMatrix *
		glm::lookAt(lightPos0, lightPos0 + glm::vec3(1.0, 0.0, 0.0), glm::vec3(0.0, -1.0, 0.0)));
	shadowTransforms.push_back(projectionMatrix *
		glm::lookAt(lightPos0, lightPos0 + glm::vec3(-1.0, 0.0, 0.0), glm::vec3(0.0, -1.0, 0.0)));
	shadowTransforms.push_back(projectionMatrix *
		glm::lookAt(lightPos0, lightPos0 + glm::vec3(0.0, 1.0, 0.0), glm::vec3(0.0, 0.0, 1.0)));
	shadowTransforms.push_back(projectionMatrix *
		glm::lookAt(lightPos0, lightPos0 + glm::vec3(0.0, -1.0, 0.0), glm::vec3(0.0, 0.0, -1.0)));
	shadowTransforms.push_back(projectionMatrix *
		glm::lookAt(lightPos0, lightPos0 + glm::vec3(0.0, 0.0, 1.0), glm::vec3(0.0, -1.0, 0.0)));
	shadowTransforms.push_back(projectionMatrix *
		glm::lookAt(lightPos0, lightPos0 + glm::vec3(0.0, 0.0, -1.0), glm::vec3(0.0, -1.0, 0.0)));


	for (int i = 0; i < 6; i++) {
		std::string temp = "shadowMatrices[" + std::to_string(i) + "]";
		shader.setUniformMatrix4fv(temp.c_str(), GL_FALSE, shadowTransforms[i]);
	}


}


void updateInput(GLFWwindow* window, glm::vec3& positon, glm::vec3& cameraFront, glm::vec3& cameraUp) {
	//const float cameraSpeed = 0.01f; // adjust accordingly
	//if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	//	positon += cameraSpeed * cameraFront;
	//if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	//	positon -= cameraSpeed * cameraFront;
	//if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	//	positon -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	//if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	//	positon += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	//

	//return;

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		positon.z -= 0.01f;
	else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		positon.z += 0.01f;
	else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		positon.x += 0.01f;
	else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		positon.x -= 0.01f;
	else if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
		positon.y += 0.01f;
	else if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
		positon.y -= 0.01f;
	else if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
		cameraFront.z += 0.01f;
	else if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
		cameraFront.z -= 0.01f;
	else if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
		cameraFront.y += 0.01f;
	else if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)
		cameraFront.y -= 0.01f;
	else if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS)
		cameraFront.x += 0.01f;
	else if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS)
		cameraFront.x -= 0.01f;
}

int main() {
	glfwInit();

	int glMajorVer = 4;
	int glMinorVer = 4;
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, glMajorVer);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, glMinorVer);
	glfwWindowHint(GLFW_RESIZABLE, true);

	const int WINDOW_WIDTH = 800;
	const int WINDOW_HEIGHT = 600;
	GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "MY WINDOW", NULL, NULL);
	if (window == nullptr) {
		std::cout << "no";
		glfwTerminate();
	}


	//glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

	int framebufferheight = WINDOW_WIDTH;
	int framebufferwidth = WINDOW_HEIGHT;
	glfwGetFramebufferSize(window, &framebufferwidth, &framebufferheight);
	glfwSetFramebufferSizeCallback(window, framebuffer_resize_callback);
	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		std::cout << "ok";
		glfwTerminate();
	}

	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_FRAMEBUFFER_SRGB);


	unsigned int vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	unsigned int vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * noOfBoxVertices * 8, NULL, GL_STATIC_DRAW);
	std::cout << noOfBoxVertices << std::endl;
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float) * noOfBoxVertices * 3, &vertices_box);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(float) * noOfBoxVertices * 3, sizeof(float) * noOfBoxVertices * 3, &normal);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(float) * noOfBoxVertices * 6, sizeof(float) * noOfBoxVertices * 2, &texcoord);


	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(sizeof(float) * noOfBoxVertices * 3));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)(sizeof(float) * noOfBoxVertices * 6));
	glEnableVertexAttribArray(2);

	unsigned int ibo;
	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, noOfIndices * sizeof(GLuint), indices, GL_STATIC_DRAW);

	unsigned int cubevao;
	glGenVertexArrays(1, &cubevao);
	glBindVertexArray(cubevao);

	unsigned int cubevbo;
	glGenBuffers(1, &cubevbo);
	glBindBuffer(GL_ARRAY_BUFFER, cubevbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * noOfVertices * 8, vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), 0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), ((void*)(3 * sizeof(float))));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), ((void*)(6 * sizeof(float))));
	glEnableVertexAttribArray(2);

	/*glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texcoord));
	glEnableVertexAttribArray(2);*/





	/*unsigned int ibo;
	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, noOfIndices * sizeof(GLuint), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), 0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texcoord));
	glEnableVertexAttribArray(2);

	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
	glEnableVertexAttribArray(3);
	*/


	Shader prog_final("floorVertexShader.glsl", "floorFragmentShader.glsl", "");
	Texture texture0("images/floor.png", GL_TEXTURE_2D, 1);
	glm::vec3 camPosition(0.f, 4.0f, 1.0f);
	glm::vec3 position(0.f, 0.f, 2.f);
	glm::vec3 rotation(10.f, 10.f, 0.f);
	glm::vec3 scale(30.f);
	glm::vec3 worldUp(0.f, 1.f, 0.f);
	glm::vec3 camFront(0.f, 0.f, 0.f);
	glm::vec3 lightPos(-2.0f, 10.0f, 1.0f);
	//prog_final.Use();
	/*glBindVertexArray(0);
	unsigned int vao1;
	glGenVertexArrays(1, &vao1);
	glBindVertexArray(vao1);

	unsigned int vbo1;
	glGenBuffers(1, &vbo1);
	glBindBuffer(GL_ARRAY_BUFFER, vbo1);
	glBufferData(GL_ARRAY_BUFFER, noOfBoxVertices2*5*sizeof(float), &quadVertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);*/

	unsigned int quadVAO, quadVBO;
	glGenVertexArrays(1, &quadVAO);
	glGenBuffers(1, &quadVBO);
	glBindVertexArray(quadVAO);
	glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));


	/*
	//new frame buffer
	unsigned int fbo;
	glGenFramebuffers(1, &fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);

	unsigned int textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,framebufferwidth,framebufferheight, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureID, 0);

	unsigned int rbo;
	glGenRenderbuffers(1, &rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, framebufferwidth, framebufferheight);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);

	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER,rbo);
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;

	//glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	*/



	//unsigned int framebuffer;
	//glGenFramebuffers(1, &framebuffer);
	//glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
	//// create a color attachment texture
	//unsigned int textureColorbuffer;
	//glGenTextures(1, &textureColorbuffer);
	//glBindTexture(GL_TEXTURE_2D, textureColorbuffer);
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, WINDOW_WIDTH, WINDOW_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColorbuffer, 0);
	//// create a renderbuffer object for depth and stencil attachment (we won't be sampling these)
	//unsigned int rbo;
	//glGenRenderbuffers(1, &rbo);
	//glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	//glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, WINDOW_WIDTH, WINDOW_HEIGHT); // use a single renderbuffer object for both a depth AND stencil buffer.
	//glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo); // now actually attach it
	//// now that we actually created the framebuffer and added all attachments we want to check if it is actually complete now
	//if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	//	std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
	//glBindFramebuffer(GL_FRAMEBUFFER, 0);
	//glBindRenderbuffer(GL_RENDERBUFFER, 0);




	int SHADOW_HEIGHT = 1024;
	int SHADOW_WIDTH = 1024;

	frameBuffer depthMapFBO(SHADOW_WIDTH, SHADOW_HEIGHT);

	depthMapFBO.unBindBuffer();

	//prog_final.Use();
	prog_final.setUniform1i("texture0", 0);
	Shader prog_final1("skyboxVertexShader.glsl", "skyboxFragmentShader.glsl", "");

	Shader shad("planetVertexShader.glsl", "planetFragmentShader.glsl", "planetGeometryShader.glsl");

	Model plan("objFile/planet/planet.obj");

	Shader simple("simpleVertexShader.glsl", "simpleFragmentShader.glsl", "simpleGeometryShader.glsl");

	Shader prog_box("cube3Dvertexshader.glsl", "cube3Dfragmentshader.glsl", "cube3DgeometryShader.glsl");


	while (!glfwWindowShouldClose(window)) {
		//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		glEnable(GL_CULL_FACE);
		glCullFace(GL_FRONT);
		glFrontFace(GL_CCW);
		glfwPollEvents();
		glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
		depthMapFBO.bindBuffer();
		glClear(GL_DEPTH_BUFFER_BIT);
		updateInput(window, camPosition, lightPos, worldUp);
		simple.Use();
		updateShadow(window, simple, glm::vec3(0.f, 0.5f, 0.f), glm::vec3(0.f), glm::vec3(1.f), camPosition, lightPos, camFront, worldUp);
		simple.Use();
		//depthMapFBO.bindMe();
		//planet.setUniformMatrix4fv("modelMatrix", GL_FALSE, modelMatrix);
		simple.setUniform1f("time", (float)glfwGetTime());
		plan.Draw(&simple);

		updateShadow(window, simple, glm::vec3(-1.f, 9.f, 0.f), rotation, glm::vec3(1.f), camPosition, lightPos, camFront, worldUp);
		//depthMapFBO.bindMe();
		plan.Draw(&simple);

		simple.Use();

		updateShadow(window, simple, position, rotation, scale, camPosition, lightPos, camFront, worldUp);
		simple.Use();
		//depthMapFBO.bindMe();
		//texture0.bind();
		//simple.setUniform1i("diffTex", texture0.getTextureUnit());
		glBindVertexArray(vao);

		//glDrawElements(GL_TRIANGLES, noOfIndices, GL_UNSIGNED_INT, 0);
		//glDisable(GL_CULL_FACE);
		//simple.Use();
		//updateUniforms(window, simple, glm::vec3(0.f), rotation, glm::vec3(0.25f), camPosition, lightPos, camFront, worldUp);
		//glBindVertexArray(cubevao);
		//glDrawArrays(GL_TRIANGLES, 0, noOfVertices);

		//updateShadow(window, simple, position + glm::vec3(0.25f, 0.f, 0.f), rotation, scale, camPosition, lightPos, camFront, worldUp);
		//glDrawElements(GL_TRIANGLES, noOfIndices, GL_UNSIGNED_INT, 0);
		//glBindFramebuffer(GL_FRAMEBUFFER, 0);



		// render

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
		glDisable(GL_CULL_FACE);
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		glfwPollEvents();
		updateInput(window, camPosition, lightPos, worldUp);
		shad.Use();
		updateUniforms(window, shad, glm::vec3(0.f, 0.5f, 0.f), glm::vec3(0.f), glm::vec3(1.f), camPosition, lightPos, camFront, worldUp);
		shad.Use();
		//planet.setUniformMatrix4fv("modelMatrix", GL_FALSE, modelMatrix);
		shad.setUniform1f("time", (float)glfwGetTime());
		shad.setUniform1i("depthMap", 3);
		depthMapFBO.bindTexture(3);
		plan.Draw(&shad);
		updateInput(window, camPosition, lightPos, worldUp);

		updateUniforms(window, shad, glm::vec3(-1.f, 9.f, 0.f), rotation, glm::vec3(1.f), camPosition, lightPos, camFront, worldUp);
		shad.setUniform1i("depthMap", 3);
		depthMapFBO.bindTexture(3);
		plan.Draw(&shad);

		updateInput(window, camPosition, lightPos, worldUp);
		/*glEnable(GL_CULL_FACE);
		glCullFace(GL_FRONT);
		glFrontFace(GL_CCW);*/
		updateUniforms(window, shad, lightPos, rotation, glm::vec3(0.25f), camPosition, lightPos, camFront, worldUp);
		plan.Draw(&shad);
		//glEnable(GL_STENCIL_TEST);
		//glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
		/*glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		glfwPollEvents();
		updateInput(window, camPosition, camFront,worldUp);*/
		prog_final.Use();

		prog_final.setUniform1i("depthMap", 0);
		depthMapFBO.bindTexture(0);
		updateUniforms(window, prog_final, position, rotation, glm::vec3(2.f) * scale, camPosition, lightPos, camFront, worldUp);
		prog_final.Use();
		texture0.bind();
		prog_final.setUniform1i("diffTex", texture0.getTextureUnit());
		glBindVertexArray(vao);
		//glBindTexture(GL_TEXTURE_2D, depthMap);
		//glDrawElements(GL_TRIANGLES, noOfIndices, GL_UNSIGNED_INT, 0);
		glDisable(GL_CULL_FACE);
		prog_box.Use();
		updateUniforms(window, prog_box, glm::vec3(0.f), rotation, scale, camPosition, lightPos, camFront, worldUp);
		glBindVertexArray(cubevao);
		depthMapFBO.bindMe();
		texture0.bind();
		prog_box.setUniform1i("diffTex", texture0.getTextureUnit());
		//glBindTexture(GL_TEXTURE_2D, depthMap);
		glDrawArrays(GL_TRIANGLES, 0, noOfVertices);
		//updateUniforms(window, prog_final, position + glm::vec3(0.25f, 0.f, 0.f), rotation, scale, camPosition, lightPos, camFront, worldUp);
		//glDrawElements(GL_TRIANGLES, noOfIndices, GL_UNSIGNED_INT, 0);

		/*
		//glfwPollEvents();
		prog_final1.Use();
		glBindFramebuffer(GL_FRAMEBUFFER, fbo);
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glDisable(GL_DEPTH_TEST);
		glDisable(GL_STENCIL);
		glfwPollEvents();
		updateInput(window, position, camFront, worldUp);

		updateUniforms(window, prog_final1, position, rotation, scale, camPosition, lightPos, camFront, worldUp);
		prog_final1.Use();
		glBindVertexArray(vao1);
		glDrawArrays(GL_TRIANGLES, 0, noOfBoxVertices2);

		glBindFramebuffer(GL_FRAMEBUFFER, 0);*/

		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		//glDisable(GL_DEPTH_TEST); // disable depth test so screen-space quad isn't discarded due to depth test.
		// clear all relevant buffers

		//glClearColor(1.0f, 1.f, 1.0f, 1.0f); // set clear color to white (not really necessery actually, since we won't be able to see behind the quad anyways)
		//glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
		//
		//prog_final1.Use();
		//glBindVertexArray(quadVAO);
		//updateInput(window, camPosition, camFront, worldUp);
		//updateUniforms(window, prog_final1, position, rotation, scale, camPosition, lightPos, camFront, worldUp);
		////glActiveTexture(GL_TEXTURE0);
		//prog_final1.setUniform1i("texture0", 0);
		//glBindTexture(GL_TEXTURE_2D, textureColorbuffer);	// use the color attachment texture as the texture of the quad plane
		//glDrawArrays(GL_TRIANGLES, 0, 6);

		//glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
		//glClearColor(1.0f, 1.f, 1.0f, 1.0f); // set clear color to white (not really necessery actually, since we won't be able to see behind the quad anyways)
		//glClear(GL_DEPTH_BUFFER_BIT);

		//prog_final1.Use();
		//glBindVertexArray(quadVAO);
		//updateInput(window, camPosition, camFront, worldUp);
		//updateUniforms(window, prog_final1, position, rotation, scale, camPosition, lightPos, camFront, worldUp);
		////glActiveTexture(GL_TEXTURE0);
		//prog_final1.setUniform1i("texture0", 0);
		////texture0.bind();
		//glBindTexture(GL_TEXTURE_2D, textureColorbuffer);	// use the color attachment texture as the texture of the quad plane
		//glDrawArrays(GL_TRIANGLES, 0, 6);

		glBindVertexArray(0);

		glBindVertexArray(0);


		glfwSwapBuffers(window);
		glfwPollEvents();

	}
	glfwTerminate();
	return 0;

}