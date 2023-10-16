#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

int main(void)
{

    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Learn OPENGL", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        /* Problem: glewInit failed, something is seriously wrong. */
        std::cout << "Error: " << glewGetErrorString(err) << std::endl;
        return -1;
    }
    std::cout << "Status: Using GLEW " << glewGetString(GLEW_VERSION) << std::endl;
    std::cout << "Status: Using OPENGL " << glGetString(GL_VERSION) << std::endl;

    float coordinates[9] = {
        -0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f,
         0.5f, -0.5f, 0.0f
    };

    unsigned int triangleBuffer;
    glGenBuffers(1, &triangleBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, triangleBuffer);
    glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), coordinates, GL_STATIC_DRAW);

    const char* vertexShaderSource = "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "void main()\n"
        "{\n"
        " gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "}\0";

    unsigned int vertexShaderId;
    vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShaderId, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShaderId);

    int success;
    glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        char infoLogVS[512];
        glGetShaderInfoLog(vertexShaderId, 512, NULL, infoLogVS);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLogVS << std::endl;
        return -1;
    }

    const char* fragmentShaderSource = "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        " FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
        "}\0";

    unsigned int fragShaderId;
    fragShaderId = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragShaderId, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragShaderId);

    success = 0;
    glGetShaderiv(fragShaderId, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        char infoLogFS[512];
        glGetShaderInfoLog(fragShaderId, 512, NULL, infoLogFS);
        std::cout << "ERROR::SHADER::FARGMENT::COMPILATION_FAILED\n" << infoLogFS << std::endl;
        return -1;
    }

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);
        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}