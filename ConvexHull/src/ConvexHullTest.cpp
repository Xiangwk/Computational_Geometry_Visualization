#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <cmath>

#include <vector>
#include <random>
#include <ctime>

#include "..\include\MyShader.h"
#include "..\include\ConvexHull.h"

enum VAO_IDs{Points, ConvexHull, NumVAOs};
enum Buffer_IDs{pBuffer, chBuffer, NumBuffers};

GLuint VAOs[NumVAOs];
GLuint Buffers[NumBuffers];

//GLFW window option
void InitwWindowOption();
//key callback
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

int main()
{
	//std::vector<cg::Point> vp{ { 10, 10 }, { 20, 10 }, { 30, 10 }, { 40, 10 }, { 50, 10 }, { 60, 60 } };
	std::default_random_engine e(time(0));
	std::uniform_int_distribution<unsigned> u(1, 99);

	std::vector<cg::Point> vp;
	for (size_t i = 0; i < 100; ++i)
	{
		int x = u(e);
		int y = u(e);
		vp.push_back(cg::Point(x, y));
	}

	std::vector<cg::Point> ch;
	grahamScan(vp, ch);

	/*std::cout << "vp: " << std::endl;
	for (const auto &p : vp)
		std::cout << p.x << " " << p.y << std::endl;*/

	/*std::cout << "ch: " << std::endl;
	for (const auto &p : ch)
		std::cout << p.x << " " << p.y << std::endl;
	std::cout << std::endl;*/

	std::cout << "OpenGL 3.3 GO!" << std::endl;

	InitwWindowOption();

	//create window
	GLFWwindow *window = glfwCreateWindow(800, 600, "Convex Hull", nullptr, nullptr);
	if (window == 0)
	{
		std::cout << "GLFW Window create fail!" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	//init glew, pay attention that GLEW_OK == 0
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		std::cout << "GLEW init fail£¡" << std::endl;
		return -1;
	}

	//create viewport
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);
	//set the background color
	glClearColor(0.9, 0.9, 0.9, 1.0);

	glfwSetKeyCallback(window, key_callback);

	Shader shader("../shader/vertShader.vert", "../shader/fragShader.frag");

	//set vertex attribute
	GLuint VAOs[NumVAOs];
	glCreateVertexArrays(NumVAOs, VAOs);
	glBindVertexArray(VAOs[Points]);

	GLuint VBOs[NumBuffers];
	glCreateBuffers(NumBuffers, VBOs);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[pBuffer]);
	glBufferData(GL_ARRAY_BUFFER, vp.size() * sizeof(cg::Point), &vp[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_INT, GL_FALSE, sizeof(cg::Point), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	glBindVertexArray(VAOs[ConvexHull]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[chBuffer]);
	glBufferData(GL_ARRAY_BUFFER, ch.size() * sizeof(cg::Point), &ch[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_INT, GL_FALSE, sizeof(cg::Point), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	glPointSize(3.0);

	//game loop
	while (!glfwWindowShouldClose(window))
	{
		//check events
		glfwPollEvents();

		glClear(GL_COLOR_BUFFER_BIT);
		//use shader
		glUseProgram(shader.program);
		//draw point set
		glBindVertexArray(VAOs[Points]);
		glDrawArrays(GL_POINTS, 0, vp.size());
		glBindVertexArray(0);
		//draw convex hull
		glBindVertexArray(VAOs[ConvexHull]);
		glDrawArrays(GL_LINE_STRIP, 0, ch.size());
		glBindVertexArray(0);

		glfwSwapBuffers(window);
	}

	glDeleteVertexArrays(NumVAOs, VAOs);
	glDeleteBuffers(NumBuffers, VBOs);
	glfwTerminate();
	std::cout << "Done!" << std::endl;

	return 0;
}

void InitwWindowOption()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}