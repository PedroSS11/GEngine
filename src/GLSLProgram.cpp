#include "GLSLProgram.h"
#include <iostream>
#include <fstream>

using namespace std;

GLSLProgram::GLSLProgram(void)
{
    m_vIdShader[VERTEX] = 0;
    m_vIdShader[FRAGMENT] = 0;
    m_vIdShader[GEOMETRY] = 0;
    m_vIdShader[TESSELATION] = 0;
}

GLSLProgram::~GLSLProgram(void)
{
    if (m_uIdProgram > 0)
    {
        glDeleteProgram(m_uIdProgram);
        printf("Program deleted");
    }
}

bool GLSLProgram::loadShaderFile(std::string strFileName, GLuint iHandle)
{
    std::ifstream shaderSource(strFileName.c_str());
    if (!shaderSource.is_open())
    {
        std::cerr << " File not found " << strFileName.c_str() << endl;
        return false;
    }
    // read in the data
    string strSource = std::string((std::istreambuf_iterator<char>(shaderSource)), std::istreambuf_iterator<char>());
    shaderSource.close();
    strSource += "\0";
    // pass the code to OGL
    const char *data = strSource.c_str();
    glShaderSource(iHandle, 1, &data, NULL);
    return true;
}

void GLSLProgram::loadShader(std::string strFileName, SHADERTYPE shaderType)
{
    GLuint hShader = 0;
    GLint status;

    // Cria o shader object
    switch (shaderType)
    {
    case VERTEX:
    {
        hShader = glCreateShader(GL_VERTEX_SHADER);
        break;
    }
    case FRAGMENT:
    {
        hShader = glCreateShader(GL_FRAGMENT_SHADER);
        break;
    }
    case GEOMETRY:
    {
        hShader = glCreateShader(GL_GEOMETRY_SHADER);
        break;
    }
    case TESSELATION:
    {
        hShader = 0;
        std::cerr << "not implemented.... yet :-)" << std::endl;
    }
    }

    if (loadShaderFile(strFileName, hShader))
    {
        glCompileShader(hShader);
        glGetShaderiv(hShader, GL_COMPILE_STATUS, &status);
        if (status == GL_FALSE)
        {
            char infoLog[1024];
            glGetShaderInfoLog(hShader, 1024, NULL, infoLog);
            cout << "The shader at " << strFileName.c_str() << " failed to compile with the following errors:" << endl
                 << infoLog << endl;
            glDeleteShader(hShader);
        }
        else
        {
            cout << "The shader at " << strFileName.c_str() << " was compiled without errors." << endl;
            m_vIdShader[shaderType] = hShader;
        }
    }
    else
    {
        std::cerr << "something wrong loading the shader located in " << strFileName.c_str() << "." << std::endl;
        glDeleteShader(hShader);
    }
}

void GLSLProgram::checkLinkingErrors()
{
    GLint infologLength = 0;
    glGetProgramiv(m_uIdProgram, GL_INFO_LOG_LENGTH, &infologLength);
    // std::cerr<<"Link Log Length "<<infologLength<<"\n";

    if (infologLength > 1)
    {
        char *infoLog = new char[infologLength];
        GLint charsWritten = 0;

        glGetProgramInfoLog(m_uIdProgram, infologLength, &charsWritten, infoLog);

        std::cerr << infoLog << std::endl;
        delete[] infoLog;
        glGetProgramiv(m_uIdProgram, GL_LINK_STATUS, &infologLength);
        if (infologLength == GL_FALSE)
        {
            std::cerr << "Program link failed exiting \n";
            exit(EXIT_FAILURE);
        }
    }
}

void GLSLProgram::createLink()
{
    m_uIdProgram = glCreateProgram();
    // attach the shaders
    if (m_vIdShader[VERTEX] > 0)
        glAttachShader(m_uIdProgram, m_vIdShader[VERTEX]);
    if (m_vIdShader[FRAGMENT] > 0)
        glAttachShader(m_uIdProgram, m_vIdShader[FRAGMENT]);
    if (m_vIdShader[GEOMETRY] > 0)
        glAttachShader(m_uIdProgram, m_vIdShader[GEOMETRY]);

    // cria o link
    glLinkProgram(m_uIdProgram);
    checkLinkingErrors();

    // delete shaders
    glDeleteShader(m_vIdShader[VERTEX]);
    glDeleteShader(m_vIdShader[FRAGMENT]);
    glDeleteShader(m_vIdShader[GEOMETRY]);
}

void GLSLProgram::enable()
{
    glUseProgram(m_uIdProgram);
}
