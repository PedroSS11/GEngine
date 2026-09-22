#pragma once

#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <string>

class GLSLProgram
{
public:
    enum SHADERTYPE
    {
        VERTEX = 0,
        FRAGMENT,
        GEOMETRY,
        TESSELATION
    };

    GLuint m_uIdProgram; // Id do programa
    GLuint m_vIdShader[4];

    GLSLProgram(void);
    ~GLSLProgram(void);

    void loadShader(std::string strFileName, SHADERTYPE shaderType);
    void checkLinkingErrors();
    void createLink();
    void enable();
    GLuint getId();

private:
    bool loadShaderFile(std::string strFileName, GLuint iHandle);
};