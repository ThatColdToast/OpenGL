#include "Graphics/IndexBuffer.h"

#include <GL/glew.h>

#include "Graphics/GLCall.h" // Includes "ASSERT"

#include "Utils/Profiling.h"

IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count)
    : m_Count(count)
{
    PROFILE_FUNCTION();
    ASSERT(sizeof(unsigned int) == sizeof(GLuint));

    GLCall(glGenBuffers(1, &m_RendererID));
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));
}

IndexBuffer::~IndexBuffer()
{
    PROFILE_FUNCTION();
    GLCall(glDeleteBuffers(1, &m_RendererID));
}

void IndexBuffer::Bind() const
{
    PROFILE_FUNCTION();
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
}

void IndexBuffer::Unbind() const
{
    PROFILE_FUNCTION();
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}
