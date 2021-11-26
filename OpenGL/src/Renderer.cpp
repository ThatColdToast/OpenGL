#include "Renderer.h"

#include <iostream>

#include "cherno/Instrumentor.h"

#include "GLCall.h"

void GLClearError()
{
    PROFILE_FUNCTION();
    while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, int line)
{
    PROFILE_FUNCTION();
    while (GLenum error = glGetError())
    {
        std::cout << "[OpenGL Error] (" << error << "): " << function <<
            " " << file << ":" << line << std::endl;
        return false;
    }
    return true;
}

void Renderer::Clear() const
{
    PROFILE_FUNCTION();
    GLCall(glClear(GL_COLOR_BUFFER_BIT));
}

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
{
    PROFILE_FUNCTION();
    shader.Bind();

    va.Bind();
    ib.Bind();

    GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
}
