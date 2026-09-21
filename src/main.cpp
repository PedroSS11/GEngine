#include <stdio.h>

#include <glad/gl.h>
#include <GLFW/glfw3.h>
// #include <glm/glm.hpp>

#define WINDOW_TITLE "GEngine"

int main()
{

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

    // glClearColor(0.5f, 0.7f, 0.3f, 1.0f);

    // VBO - Página de memória na GPU salvando buffer de vertices
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    float vertices[] = {
        0.5f, 0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
        -0.5f, 0.5f, 0.0f};

    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(vertices),
        vertices,
        GL_STATIC_DRAW);

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

    // Loop gráfico
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // coloca pra gpu oq tem de vbo e vao configurado
        glDrawArrays(GL_TRIANGLES, 0, 6);

        // Desenha o buffeer com oq foi passado antes dessa chamada
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    // std::cout<< "olha essa geometria" << std::endl;
    return 0;
}