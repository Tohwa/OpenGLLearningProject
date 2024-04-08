#include "Viewport.h"
#include <iostream>

int SViewport::Initialize(void)
{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, M_I_GLFW_VERSION_MAJOR);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, M_I_GLFW_VERSION_MINOR);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_pWindow = glfwCreateWindow(M_I_WINDOW_WIDTH, M_I_WINDOW_HEIGHT, M_S_TITLE, NULL, NULL);

    if (!m_pWindow) {

        std::cout << "ERROR: Window creation failed!" << std::endl;
        glfwTerminate();
        return -2; //ERROR: Window creation failed!
    }

    glfwMakeContextCurrent(m_pWindow);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "ERROR: GLAD INIT FAILED!" << std::endl;
        return -3;
    }

    //TODO: Shader Program compile

    return 0;
}

int SViewport::Update(void)
{
    return 0;
}

int SViewport::Draw(void)
{
    glClearColor(1.0f, 0.2f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    SVertex vertices[]{ // anti clockwise!!!            3
        glm::vec3(-0.5f, -0.5f, 0.0f),      //          *
        glm::vec3(0.5f, -0.5f, 0.0f),       //        / 0 \                                 */
        glm::vec3(0.0f, 0.5f, 0.0f)         //      1*-----*2
    };

    unsigned int VBO{}; // uint for the buffer ID
    glGenBuffers(1, &VBO); // generate the buffer ID
    glBindBuffer(GL_ARRAY_BUFFER, VBO); // bind the buffer to use it

    unsigned int VAO{}; // uint for the Vertex Array
    glGenVertexArrays(1, &VAO); // Generate the Array ID
    glBindVertexArray(VAO); // bind the Array to use it

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //TODO: Write VertexAttribPointer function
    //TODO: shaderProgram.use()

    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);

    glfwSwapBuffers(m_pWindow);

    return 0;
}

void SViewport::Finalize(void)
{
}
