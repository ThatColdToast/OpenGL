#include "VertexBuffer.h"

#include <GL/glew.h>

#include "Profiling.h"

#include "GLCall.h"

VertexBuffer::VertexBuffer(const void* data, unsigned int size)
{
    PROFILE_FUNCTION();
    GLCall(glGenBuffers(1, &m_RendererID));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
    GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

VertexBuffer::~VertexBuffer()
{
    PROFILE_FUNCTION();
    GLCall(glDeleteBuffers(1, &m_RendererID));
}

void VertexBuffer::Bind() const
{
    PROFILE_FUNCTION();
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
}

void VertexBuffer::Unbind() const
{
    PROFILE_FUNCTION();
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
