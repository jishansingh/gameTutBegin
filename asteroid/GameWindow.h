#pragma once
#include"libs.h"
void framebuffer_resize_callback(GLFWwindow* window, int width, int height);
class GameWindow {
protected:
	GLFWwindow* window;
private:
	int glMajorVer = 4;
	int glMinorVer = 4;
	
	int framebufferheight;
	int framebufferwidth;
	void initWindow() {
		glfwInit();
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, glMajorVer);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, glMinorVer);
		glfwWindowHint(GLFW_RESIZABLE, true);
	}
	void createWindow(const char *winName,int WINDOW_WIDTH,int WINDOW_HEIGHT) {
		window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, winName, NULL, NULL);
		if (window == nullptr) {
			std::cout << "no";
			glfwTerminate();
		}
		framebufferheight = WINDOW_WIDTH;
		framebufferwidth = WINDOW_HEIGHT;
	}
public:
	GameWindow(const char* winName,const int WINDOW_WIDTH=800, const int WINDOW_HEIGHT=800) {
		initWindow();
		createWindow(winName, WINDOW_WIDTH, WINDOW_HEIGHT);
		glfwGetFramebufferSize(window, &framebufferwidth, &framebufferheight);
		glfwSetFramebufferSizeCallback(window, framebuffer_resize_callback);
		glfwMakeContextCurrent(window);

		glewExperimental = GL_TRUE;
		if (glewInit() != GLEW_OK) {
			std::cout << "ok";
			glfwTerminate();
		}
	}
	virtual ~GameWindow() {
		glfwTerminate();
	}
	virtual void preRender() { }
	virtual void postRender() {}
	void render() {
		while (!glfwWindowShouldClose(window)) {
			preRender();
			postRender();
			glfwSwapBuffers(window);
			glfwPollEvents();

		}
	}


};
void framebuffer_resize_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}