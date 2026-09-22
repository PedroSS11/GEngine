#include <stdio.h>

#include <glad/gl.h>
#include <GLFW/glfw3.h>
// #include <glm/glm.hpp>

#include "GLSLProgram.h"

#define WINDOW_TITLE "GEngine"

static void error_callback(int error, const char *description)
{
    fprintf(stderr, "Error: %s\n", description);
}

void check_shader_success(GLuint shader)
{
    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        char infoLog[512];

        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        printf("Erro ao compilar shader:\n%s\n", infoLog);
    }
}

void check_program_success(GLuint program)
{
    GLint success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success)
    {
        char infoLog[512];

        glGetShaderInfoLog(program, 512, NULL, infoLog);
        printf("Erro ao linkar shader program:\n%s\n", infoLog);
    }
}

int main()
{
    GLSLProgram m_program;

    glfwSetErrorCallback(error_callback);

    if (!glfwInit())
    {
        printf("FALHA AO INICIAR  GLFW\n");
        return -1;
    }

    GLFWwindow *window = glfwCreateWindow(640, 480, WINDOW_TITLE, NULL, NULL);

    if (!window)
    {
        printf("FALHA AO CRIAR JANELA GLFW\n");
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    gladLoadGL(glfwGetProcAddress);
    fprintf(stderr, "OpenGL %s\n", glGetString(GL_VERSION));
    // Na teoria era o vsync
    // glfwSwapInterval(1);

    // glClearColor(0.5f, 0.7f, 0.3f, 1.0f);

    // VBO - Página de memória na GPU salvando buffer de vertices
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    float vertices[] = {
        0.0f, 0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f};

    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(vertices),
        vertices,
        GL_STATIC_DRAW);

    // shader
    m_program.loadShader("assets/shaders/basic.vert", GLSLProgram::VERTEX);
    m_program.loadShader("assets/shaders/basic.frag", GLSLProgram::FRAGMENT);
    m_program.createLink();
    // m_program.enable();

    // VAO - Configuração de como o vbo deve se comportar
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        3 * sizeof(float),
        (void *)0);

    glEnableVertexAttribArray(0);

    // FPS
    double prevTime = glfwGetTime();
    int frameCount = 0;
    // printf("%d", prevTime);
    // Loop gráfico
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // FPS
        double currTime = glfwGetTime();
        frameCount++;
        if (currTime - prevTime >= 1.0)
        {
            printf("FPS: %d\n", frameCount);
            frameCount = 0;
            prevTime = currTime;
        }

        // teste shader program
        // glUseProgram(program);
        m_program.enable();
        // coloca pra gpu oq tem de vbo e vao configurado
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // Desenha o buffeer com oq foi passado antes dessa chamada
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    // std::cout<< "olha essa geometria" << std::endl;
    return 0;
}