#pragma once

#include <vector>

#include <GL/glew.h>

#include "GLCall.h" // Includes "ASSERT"

struct VertexBufferElement
{
	unsigned int type;
	unsigned int count;
	unsigned char normalized;

	static unsigned int GetSizeOfType(unsigned int type)
	{
		switch (type)
		{
			case GL_FLOAT: return 4;
			case GL_UNSIGNED_INT: return 4;
			case GL_UNSIGNED_BYTE: return 1;
		}
		ASSERT(false);
		return 0;
	}
};

class VertexBufferLayout
{
private:
	std::vector<VertexBufferElement> m_Elements;
	unsigned int m_Stride;
public:
	VertexBufferLayout();

	void PushAny(unsigned int count, unsigned int OPENGL_TYPE);

	void PushFloat(unsigned int count);

	void PushUnsignedInt(unsigned int count);

	void PushUnsignedChar(unsigned int count);

	const std::vector<VertexBufferElement> GetElements() const;
	unsigned int GetStride() const;
};