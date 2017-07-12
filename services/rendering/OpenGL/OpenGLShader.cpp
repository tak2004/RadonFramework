#include <RadonFramework/precompiled.hpp>
#include "OpenGLShader.hpp"
#include <OpenGL.hpp>
#include <RadonFramework/Collections/Array.hpp>
#include <RadonFramework/IO/Log.hpp>

namespace RadonFramework::Drawing {

void OpenGLShader::Generate()
{
    const char* vertex_shader =
        "#version 420\n"
        "layout(location = 0) in vec2 vertex_position;"
        "layout(location = 1) in vec4 vertex_color;"
        "layout(std140, binding = 0) uniform SharedTransformUniforms"
        "{"
        "    mat4 ModelView;"
        "    mat4 ModelViewProjection;"
        "    mat4 UIProjection;"
        "};"
        "out vec4 rgba;"
        "void main () {"
        "  gl_Position = UIProjection*vec4(vertex_position, -1.0, 1.0);"
        "  rgba = vertex_color;"
        "}";

    const char* fragment_shader =
        "#version 420\n"
        "out vec4 frag_colour;"
        "in vec4 rgba;"
        "void main () {"
        "  frag_colour = rgba;"
        "}";

    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vertex_shader, NULL);
    glCompileShader(vs);

    GLint isCompiled = 0;
    glGetShaderiv(vs, GL_COMPILE_STATUS, &isCompiled);
    if(isCompiled == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetShaderiv(vs, GL_INFO_LOG_LENGTH, &maxLength);
        RF_Collect::Array<GLchar> errorLog(maxLength);
        glGetShaderInfoLog(vs, maxLength, &maxLength, &errorLog(0));
        RF_IO::LogError("Vertex-Shader:%s\n", &errorLog(0));
        glDeleteShader(vs);
        return;
    }

    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fragment_shader, NULL);
    glCompileShader(fs);
    glGetShaderiv(fs, GL_COMPILE_STATUS, &isCompiled);
    if(isCompiled == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetShaderiv(fs, GL_INFO_LOG_LENGTH, &maxLength);
        RF_Collect::Array<GLchar> errorLog(maxLength);
        glGetShaderInfoLog(fs, maxLength, &maxLength, &errorLog(0));
        RF_IO::LogError("Fragment-Shader:%s\n", &errorLog(0));
        glDeleteShader(fs);
        glDeleteShader(vs);
        return;
    }

    shader_programme = glCreateProgram();
    glAttachShader(shader_programme, fs);
    glAttachShader(shader_programme, vs);
    glLinkProgram(shader_programme);
    GLint isLinked = 0;
    glGetProgramiv(shader_programme, GL_LINK_STATUS, (int *)&isLinked);
    if(isLinked == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetProgramiv(shader_programme, GL_INFO_LOG_LENGTH, &maxLength);
        RF_Collect::Array<GLchar> infoLog(maxLength);
        glGetProgramInfoLog(shader_programme, maxLength, &maxLength, &infoLog(0));
        RF_IO::LogError("Fragment-Shader:%s\n", &infoLog(0));
        glDeleteProgram(shader_programme);
        glDeleteShader(vs);
        glDeleteShader(fs);
        return;
    }
    glDetachShader(shader_programme, vs);
    glDetachShader(shader_programme, fs);
    glDeleteShader(vs);
    glDeleteShader(fs);
}

void OpenGLShader::Bind()
{
    glUseProgram(shader_programme);
}

void OpenGLShader::Unbind()
{
    glUseProgram(0);
}

}