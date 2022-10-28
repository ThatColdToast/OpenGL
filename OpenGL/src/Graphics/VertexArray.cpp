#include "Graphics/VertexArray.h"

#include <GL/glew.h>

#include "Utils/Profiling.h"

#include "Graphics/GLCall.h"
#include "Graphics/VertexBufferLayout.h"

VertexArray::VertexArray()
{
	PROFILE_FUNCTION();
	GLCall(glGenVertexArrays(1, &m_RendererID));
}

VertexArray::~VertexArray()
{
	PROFILE_FUNCTION();
	GLCall(glDeleteVertexArrays(1, &m_RendererID));
}

void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
	PROFILE_FUNCTION();
	Bind();
	vb.Bind();
	const auto& elements = layout.GetElements();
	unsigned int offset = 0;

	for (unsigned int i = 0; i < elements.size(); i++)
	{
		const auto& element = elements[i];
		GLCall(glEnableVertexAttribArray(i));
		GLCall(glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(), (const void*)offset));
		offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
	}
}

void VertexArray::Bind() const
{
	PROFILE_FUNCTION();
	GLCall(glBindVertexArray(m_RendererID));
}

void VertexArray::Unbind() const
{
	PROFILE_FUNCTION();
	GLCall(glBindVertexArray(0));
}
