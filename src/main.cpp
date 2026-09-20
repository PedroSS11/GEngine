#include <stdio.h>

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

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

    while (!glfwWindowShouldClose(window))
    {
        // fica lendo eventos
        glfwPollEvents();

        glfwSwapBuffers(window);
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    // std::cout<< "olha essa geometria" << std::endl;
    return 0;
}