#include "Graphics/VertexBufferLayout.h"

#include <vector>

#include "Utils/Profiling.h"

VertexBufferLayout::VertexBufferLayout()
	: m_Stride(0) {}

void VertexBufferLayout::PushAny(unsigned int count, unsigned int OPENGL_TYPE)
{
	PROFILE_FUNCTION();
	// static_assert(false);
	m_Elements.push_back({ OPENGL_TYPE, count, false });
	m_Stride += count * VertexBufferElement::GetSizeOfType(OPENGL_TYPE);
}

void VertexBufferLayout::PushFloat(unsigned int count)
{
	PROFILE_FUNCTION();
	m_Elements.push_back({ GL_FLOAT, count, GL_FALSE });
	m_Stride += count * VertexBufferElement::GetSizeOfType(GL_FLOAT);
}

void VertexBufferLayout::PushUnsignedInt(unsigned int count)
{
	PROFILE_FUNCTION();
	m_Elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
	m_Stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT);
}

void VertexBufferLayout::PushUnsignedChar(unsigned int count)
{
	PROFILE_FUNCTION();
	m_Elements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
	m_Stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE);
}

const std::vector<VertexBufferElement> VertexBufferLayout::GetElements() const { return m_Elements; }
unsigned int VertexBufferLayout::GetStride() const { return m_Stride; }