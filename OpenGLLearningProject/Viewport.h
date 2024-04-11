#ifndef VIEWPORT_H
#define VIEWPORT_H

#include <GLAD/glad.h>
#include <GLFW/glfw3.h>
#include "Vertex.h"
#include "Shader.h"
struct SViewport
{
	SViewport() {};
	inline GLFWwindow* GetWindow() { return m_pWindow; }

	int Initialize(void);
	int Update(void);
	int Draw(void);
	int LateDraw(void);
	void Finalize(void);

private:
	GLFWwindow* m_pWindow;

	//TODO: Add Constants
	const int M_I_GLFW_VERSION_MAJOR = 3;
	const int M_I_GLFW_VERSION_MINOR = 3;

	const int M_I_WINDOW_WIDTH = 800;
	const int M_I_WINDOW_HEIGHT = 600;

	const char* M_S_TITLE = "UE2 ist toll!";
};

#endif
